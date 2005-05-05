/*
Copyright (c) 2005 mizyo
All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, provided that the above copyright notice(s) and this permission notice appear in all copies of the Software and that both the above copyright notice(s) and this permission notice appear in supporting documentation.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

Except as contained in this notice, the name of a copyright holder shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization of the copyright holder.
*/

#include "tile.h"

int mine_tile::init_tile_num = 0;
int mine_tile::bombs_num = 0;
int mine_tile::click_state = 0;
Control* mine_tile::click_sender = NULL;
Event* mine_tile::event = new Event();
bool mine_tile::start = false;

namespace {
	const int BOMB = -1;
	const int NOBOMB = 0;
	
	const int UP = 0;
	const int UPRIGHT = 1;
	const int RIGHT = 2;
	const int UNDERRIGHT = 3;
	const int UNDER = 4;
	const int UNDERLEFT = 5;
	const int LEFT = 6;
	const int UPLEFT = 7;
}

/*!
	@brief �����o�̏�����
*/
void mine_tile::initialize(){
	value = -2;
	state = init;
	init_tile_num++;
}

/*!
	@brief �^�C���̒��g��ݒ肷��
	@param new_value �^�C���̒��g�i-1:���e 0:�񔚒e�j
*/
void mine_tile::setTileValue(int new_value){
	if(value == BOMB && new_value != BOMB){
		bombs_num--;
	}
	if(value != BOMB && new_value == BOMB){
		bombs_num++;
	}
	value = new_value;
	
	repaint();
}

/*!
	@brief �`��v���V�[�W��
*/
void mine_tile::onPaint(Graphics* g){
	switch(state){
	case init:
	case init_lock:
		draw_frame(g);
		break;
	case opened:
		draw_grid(g);
		draw_number(g);
		break;
	case marked:
	case mark_lock:
		draw_frame(g);
		draw_flag(g);
		break;
	case bomb:
		draw_grid(g);
		draw_bomb(g);
		break;
	case exploded:
		draw_grid(g);
		draw_bomb(g);
		draw_cross(g);
		break;
	case missmark:
		draw_frame(g);
		draw_flag(g);
		draw_cross(g);
		break;
	default:
		break;
	}
}

/*!
	@brief �C�x���g�v���V�[�W��
*/
void mine_tile::onEvent(Event* evt){
	if(!getEnabled()){
		return;
	}

	if(evt->getType() == Event::MOUSE_PRESSED){
		//Event::MOUSE_RELEASE���ɂ́A�{�^����񂪂Ȃ�
		click_state = ((MouseEvent*)evt)->getButton();
		click_sender = this;
		return;
	}
	
	if(evt->getType() == Event::MOUSE_RELEASED){
		if(click_sender == this){
			MouseEvent* mouse = (MouseEvent*)evt;
			mouse->setButton(click_state);
			clickProc(mouse);
		}
		click_state = 0;
		click_sender = NULL;
	}
}

/*!
	@brief �܂�������Ă��Ȃ��^�C����`�悷��
	@param g �`���
*/
void mine_tile::draw_frame(Graphics* g){
	static const int A = 0xFFAAAAAA;
	static const int B = 0xFF888888;
	static const int C = 0xFF444444;
	static const int frame_dot[16][16] = {
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,C},
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,C,C},
		{A,A,A,A,A,A,A,A,A,A,A,A,A,C,C,C},
		{A,A,A,B,B,B,B,B,B,B,B,B,B,C,C,C},
		{A,A,A,B,B,B,B,B,B,B,B,B,B,C,C,C},
		{A,A,A,B,B,B,B,B,B,B,B,B,B,C,C,C},
		{A,A,A,B,B,B,B,B,B,B,B,B,B,C,C,C},
		{A,A,A,B,B,B,B,B,B,B,B,B,B,C,C,C},
		{A,A,A,B,B,B,B,B,B,B,B,B,B,C,C,C},	
		{A,A,A,B,B,B,B,B,B,B,B,B,B,C,C,C},
		{A,A,A,B,B,B,B,B,B,B,B,B,B,C,C,C},
		{A,A,A,B,B,B,B,B,B,B,B,B,B,C,C,C},
		{A,A,A,B,B,B,B,B,B,B,B,B,B,C,C,C},
		{A,A,A,C,C,C,C,C,C,C,C,C,C,C,C,C},	
		{A,A,C,C,C,C,C,C,C,C,C,C,C,C,C,C},
		{A,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C}
	};
		bit_blt(g, &frame_dot[0][0]);
}

/*!
	@brief �^�C���������ꂽ��́A�O���b�h��`�悷��
	@param g �`���
*/
void mine_tile::draw_grid(Graphics* g){
	static const int A = 0xFF444444;
	static const int B = 0xFF888888;

	static const int grid_dot[16][16] = {
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
		{A,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B}
	};

	bit_blt(g, &grid_dot[0][0]);
}

/*!
	@brief �����i�P�`�W�j��`�悷��B
	@param g �`���
*/
void mine_tile::draw_number(Graphics* g){
	if(value == 0){
		//��������
		return;
	}
	
	static const int A = 0xFFFFFFFF;
	static const int B = 0xFF0000FF;
	static const int C = 0xFF00FF00;
	static const int D = 0xFFFF0000;
	static const int E = 0xFF00CCCC;
	static const int F = 0xFFCCCC00;
	static const int G = 0xFFCC00CC;
	static const int H = 0xFF00AAAA;
	static const int I = 0xFFAA00AA;
	static const int number_dot[8][16][16] = {
		{
			/* 1 */
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,B,B,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,B,B,B,A,A,A,A,A,A},
			{A,A,A,A,A,A,B,B,B,B,A,A,A,A,A,A},
			{A,A,A,A,A,B,A,B,B,B,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,B,B,B,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,B,B,B,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,B,B,B,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,B,B,B,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,B,B,B,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,B,B,B,A,A,A,A,A,A},
			{A,A,A,A,A,B,B,B,B,B,B,B,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A}
		},
		{
			/* 2 */
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,C,C,C,C,A,A,A,A,A,A},
			{A,A,A,A,A,C,C,A,A,C,C,A,A,A,A,A},
			{A,A,A,A,A,C,C,A,A,A,C,C,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,C,C,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,C,C,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,C,C,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,C,C,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,C,C,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,C,C,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,C,C,C,C,C,C,C,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A}
		},
		{
			/* 3 */
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,D,D,D,D,D,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,D,D,D,D,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,D,D,D,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,D,D,D,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,D,D,D,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,D,D,A,A,A,A},
			{A,A,A,A,A,A,A,D,D,D,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,D,D,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,D,D,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,D,D,D,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,D,D,D,A,A,A},
			{A,A,A,A,A,A,A,A,D,D,D,D,A,A,A,A},
			{A,A,A,A,A,D,D,D,D,D,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A}
		},
		{
			/* 4 */
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,E,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,E,E,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,E,E,E,A,A,A,A,A,A,A},
			{A,A,A,A,A,E,E,E,E,A,A,A,A,A,A,A},
			{A,A,A,A,E,E,A,E,E,A,A,A,A,A,A,A},
			{A,A,A,E,E,A,A,E,E,A,A,A,A,A,A,A},
			{A,A,A,A,E,A,A,E,E,A,A,A,A,A,A,A},
			{A,A,A,A,A,E,E,E,E,E,E,E,A,A,A,A},
			{A,A,A,A,A,A,A,E,E,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,E,E,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,E,E,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,E,E,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A}
		},
		{
			/* 5 */
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,F,F,F,F,F,F,F,F,A,A,A,A},
			{A,A,A,A,F,F,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,F,F,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,F,F,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,F,F,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,F,F,F,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,F,F,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,F,F,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,F,F,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,F,F,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,F,F,A,A,A,A,A},
			{A,A,A,A,A,F,F,F,F,F,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A}
		},
		{
			/* 6 */
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,G,G,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,G,G,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,G,G,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,G,G,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,G,G,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,G,A,A,A,G,G,G,A,A,A,A,A},
			{A,A,A,A,G,A,G,G,A,A,A,G,A,A,A,A},
			{A,A,A,A,G,G,A,A,A,A,A,G,A,A,A,A},
			{A,A,A,A,G,G,A,A,A,A,A,G,A,A,A,A},
			{A,A,A,A,A,G,G,A,A,G,G,A,A,A,A,A},
			{A,A,A,A,A,A,G,G,G,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A}
		},
		{
			/* 7 */
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,H,H,H,H,H,H,H,A,A,A,A},
			{A,A,A,A,A,H,H,H,H,H,H,H,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,H,H,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,H,H,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,H,H,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,H,H,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,H,H,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,H,H,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,H,H,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,H,H,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,H,H,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,H,H,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A}
		},
		{
			/* 8 */
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,I,I,I,I,A,A,A,A,A,A},
			{A,A,A,A,I,I,A,A,A,A,I,I,A,A,A,A},
			{A,A,A,A,I,A,A,A,A,A,A,I,A,A,A,A},
			{A,A,A,A,I,A,A,A,A,A,A,I,A,A,A,A},
			{A,A,A,A,I,I,A,A,A,A,I,I,A,A,A,A},
			{A,A,A,A,A,A,I,I,I,I,A,A,A,A,A,A},
			{A,A,A,A,I,I,A,A,A,A,I,I,A,A,A,A},
			{A,A,A,A,I,A,A,A,A,A,A,I,A,A,A,A},
			{A,A,A,A,I,A,A,A,A,A,A,I,A,A,A,A},
			{A,A,A,A,I,I,A,A,A,A,I,I,A,A,A,A},
			{A,A,A,A,A,A,I,I,I,I,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
			{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A}
		},
	};
	
	bit_blt(g, &number_dot[value-1][0][0]);
}

/*!
	@brief ���e��`�悷��
	@param g �`���
*/
void mine_tile::draw_bomb(Graphics* g){
	static const int A = 0xFFFFFFFF;
	static const int B = 0xFF000000;
	static const int C = 0xFFFF0000;
	
	static const int bomb_dot[16][16] = {
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
		{A,A,A,A,C,A,C,C,A,C,C,A,C,A,A,A},
		{A,A,A,A,A,C,A,A,C,A,A,C,A,A,A,A},
		{A,A,A,A,A,A,C,C,C,C,C,A,A,A,A,A},
		{A,A,A,A,A,A,B,B,B,B,A,A,A,A,A,A},
		{A,A,A,A,A,B,B,B,B,B,B,A,A,A,A,A},
		{A,A,A,A,B,B,B,B,B,B,B,B,A,A,A,A},
		{A,A,A,A,B,B,B,B,B,B,B,B,A,A,A,A},
		{A,A,A,A,B,B,B,B,B,B,B,B,A,A,A,A},
		{A,A,A,A,B,B,B,B,B,B,B,B,A,A,A,A},
		{A,A,A,A,A,B,B,B,B,B,B,A,A,A,A,A},
		{A,A,A,A,A,A,B,B,B,B,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A}
	};
	
	bit_blt(g, &bomb_dot[0][0]);
}

/*!
	@brief ����`�悷��
	@param g �`���
*/
void mine_tile::draw_flag(Graphics* g){
	static const int A = 0xFFFFFFFF;
	static const int B = 0xFF000000;
	static const int C = 0xFFFF0000;

	static const int flag_dot[16][16] = {
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,C,C,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,C,C,C,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,C,C,C,C,C,A,A,A,A},
		{A,A,A,A,A,A,A,C,C,C,C,C,A,A,A,A},
		{A,A,A,A,A,A,A,C,C,C,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,C,C,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,B,B,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,B,B,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,B,B,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,B,B,B,B,A,A,A,A,A,A},
		{A,A,A,A,A,B,B,B,B,B,B,A,A,A,A,A},
		{A,A,A,A,B,B,B,B,B,B,B,B,A,A,A,A},
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
	};

	bit_blt(g, &flag_dot[0][0]);
}

/*!
	@biref �ԐF�́~��`�悷��
	@param g �`���
*/
void mine_tile::draw_cross(Graphics* g){
	static const int A = 0xFFFFFFFF;
	static const int B = 0xFFFF0000;

	static const int cross_dot[16][16] = {
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
		{A,A,B,A,A,A,A,A,A,A,A,A,A,B,A,A},
		{A,A,A,B,A,A,A,A,A,A,A,A,B,A,A,A},
		{A,A,A,A,B,A,A,A,A,A,A,B,A,A,A,A},
		{A,A,A,A,A,B,A,A,A,A,B,A,A,A,A,A},
		{A,A,A,A,A,A,B,A,A,B,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,B,B,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,B,B,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,B,A,A,B,A,A,A,A,A,A},
		{A,A,A,A,A,B,A,A,A,A,B,A,A,A,A,A},
		{A,A,A,A,B,A,A,A,A,A,A,B,A,A,A,A},
		{A,A,A,B,A,A,A,A,A,A,A,A,B,A,A,A},
		{A,A,B,A,A,A,A,A,A,A,A,A,A,B,A,A},
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A},
		{A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A}
	};

	bit_blt(g, &cross_dot[0][0]);
}

/*!
	@brief 16 x 16�̗̈�ɕ`�悷��
	@param g �`���
	@param bit �`�悷��F�f�[�^�Bint(unsigned int)�^�̔z��
	@note 0xFFFFFFFF�͓���
*/
void mine_tile::bit_blt(Graphics* g, const int* bit){
	static const int Alpha = 0xFFFFFFFF;
	for(int y=0; y<16; y++){
		for(int x=0; x<16; x++, bit++){
			if(*bit != Alpha){
				g->drawPixel(x, y, *bit);
			}
		}
	}
}

/*!
	@brief �p�l�����N���b�N���ꂽ�Ƃ��̏���
*/
void mine_tile::clickProc(MouseEvent* evt){
	if(evt->getButton() & 0x02 != 0){
		//���N���b�N
		if(state == init || state == marked){
			if(value == BOMB){
				state = exploded;
				send_gameover_to_tiles();
				send_gameover_to_parent();
				repaint();
			} else {
				tiles_open();
			}
			check_gameclear();
		}
	} else {
		//�E�N���b�N
		if(state == init){
			state = marked;
			repaint();
		} else if(state == marked){
			state = init;
			repaint();
		}
	}
}

/*!
	@brief �^�C���̒��g��Ԃ�
*/
int mine_tile::getTileValue(){
	return value;
}

/*!
	@brief ���Ӄ^�C���̏���ݒ肷��
	@param up ��̃^�C�����w���|�C���^�@�Ȃ��ꍇ��NULL
	@param upright �E��́V
	@param right �E�́V
	@param underright �E���́V
	@param under ���́V
	@param underleft �����́V
	@param left ���́V
	@param upleft ����́V
*/
void mine_tile::setAround(mine_tile* up, mine_tile* upright, mine_tile* right, mine_tile* underright, mine_tile* under, mine_tile* underleft, mine_tile* left, mine_tile* upleft){
	around[UP] = up;
	around[UPRIGHT] = upright;
	around[RIGHT] = right;
	around[UNDERRIGHT] = underright;
	around[UNDER] = under;
	around[UNDERLEFT] = underleft;
	around[LEFT] = left;
	around[UPLEFT] = upleft;
	
	count_around_bombs_num();
}

/*!
	@brief �����̎��ӂP�^�C�����ɂ��锚�e�̐��𐔂���
*/
void mine_tile::count_around_bombs_num(){
	if(value == BOMB){
		return;
	}
	
	int bomb_num = 0;
	for(int i=0; i<8; i++){
		if(around[i] != NULL && around[i]->value == BOMB){
			bomb_num++;
		}
	}
	
	value = bomb_num;
}

/*!
	@brief �^�C�����J�������@�ċN�I�Ɏ���̃^�C���������Ă��� 
*/
void mine_tile::tiles_open(){	
	state = opened;
	init_tile_num--;
	repaint();
	send_gamestart_to_parent();
	
	for(int i=0; i<8; i++){
		if(around[i] != NULL && 
		   (around[i]->value == BOMB || around[i]->state == marked)){
			//�אڂ���^�C���ɔ��e���A���^�C������������A�����ĊJ���Ȃ�
			return;
		}
	}
	
	for(int i=0; i<8; i++){
		if(around[i] != NULL && around[i]->state == init){
			around[i]->tiles_open();
		}
	}
}

/*!
	@brief �C�x���g�𗘗p���āA�e�E�C���h�E�ɃQ�[���I�[�o�[��ʒm����
*/
void mine_tile::send_gameover_to_parent(){
	event->arg1 = GAMEOVER;
	event->setType(Event::CUSTOM_EVENT);
	event->setSource(this);
	getParent()->onEvent(event);
}

void mine_tile::send_clear_to_parent(){
	event->arg1 = GAMECLEAR;
	event->setType(Event::CUSTOM_EVENT);
	event->setSource(this);
	getParent()->onEvent(event);
}

void mine_tile::send_gamestart_to_parent(){
	if(!start){
		event->arg1 = GAMESTART;
		event->setType(Event::CUSTOM_EVENT);
		event->setSource(this);
		getParent()->onEvent(event);
		start = true;
	}
}

/*!
	@brief �S�Ẵ^�C���ɃQ�[���I�[�o�[��`����B
	       �܂��J����Ă��Ȃ����e�^�C�����J���A
	       ����ăt���O�̂��Ă��Ă���^�C���́A�~�������
*/
void mine_tile::send_gameover_to_tiles(){
	mine_tile* current = this;
	
	//��ԍ���iup == NULL && left == NULL)�̃^�C���ֈړ�
	while(current->around[UP] != NULL){
		current = current->around[UP];
	}
	while(current->around[LEFT] != NULL){
		current = current->around[LEFT];
	}
	
	//�������N�_�ɍċN
	current->open_tile_on_gameover();
}

/*!
	@brief mile_tile::send_gameover_to_tiles()�̉������ċN�֐�
*/
void mine_tile::open_tile_on_gameover(){
	if(state == init){
		if(value == BOMB){
			state = bomb;
			repaint();
		} else {
			state = init_lock;
		}
	} else if(state == marked){
		if(value != BOMB){
			state = missmark;
			repaint();
		} else {
			state = mark_lock;
		}
	}
	
	mine_tile* current;
	if(around[RIGHT] == NULL){
		if(around[UNDER] == NULL){
			return;
		}
		current = around[UNDER];
		while(current->around[LEFT] != NULL){
			current = current->around[LEFT];
		}
		current->open_tile_on_gameover();
	} else {
		around[RIGHT]->open_tile_on_gameover();
	}
}

/*!
  @brief �Q�[���N���A�����肷��
*/
void mine_tile::check_gameclear(){
	if(init_tile_num == bombs_num){
		send_clear_to_parent();
		send_gameover_to_tiles();
	}
}
