/* Kukuri for Mona
 * 
 * Copyright (c) 2000 h-muro
 * Copyright (c) 2004 Tino, Higepon
 * 
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies of
 * the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT
 * OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL
 * INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING
 * FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

// This file's encoding is UTF-8.

#include "Kukuri.h"
#include <gui/System/Mona/Forms/Application.h>
#include <gui/System/Mona/Forms/Cursor.h>
#include <gui/messages.h>
#include <monapi.h>

using namespace System;
using namespace System::Drawing;
using namespace System::Mona::Forms;

extern dword __gui_server;
extern _P<MonAPI::Screen> GetDefaultScreen();

static MonAPI::Random rand;


Kukuri::Kukuri()
{
  nowCount = 0;
  count = 2;
  auto_x = 0;
  auto_y = 0;
  tmpo = 0;
  nowPix = 0;
  
  px = 0; py = 0;   // x����, y����
  d =  2;           // ����
  r = 90;           // �p�x
  t_num =  0;       // ��]����XPM �̏��� (turning_number)
                    // �y�� turn(),byebye(),wow()�ł̌o�߃J�E���g
  distance = 0;     // �}�E�X�ƃ|�C���^�̋���
  s_pixmap = 0;     // �Q�Ă�Ƃ��̉摜�̔ԍ�
  n_state = 1;      // ���ʎ��̏�� (normal_state)
  a_state = 0;      // �������̏�� (auto_state)
  w_num = 0;        // �����Ƃ���XPM�v�Z�p (walking_number)
  a_t_num = 0;      // ��]�̌�o�߂�������(�J�E���g)
                    //      (number_after_turning)
  a_t_dir = 0;      // ��]��ǂ���ɂ���邩
                    //      (direction_after_turning)
  a_t_dir2= 0;      // ��ɓ���
  s_interval = 0;   // ����܂ł̃J�E���g (sleep_interval)
  s_count = 0;      // �����Ă���̃J�E���g (sleep_count)
  a_flag = true;    // �������[�h�ŕ����]�����邩(�������[�h��)
                    // �������[�h�ł��邩�ǂ���(���s�쐬��)
                    //      (auto_flag)
  th_num = 0;       // �l������ XPM �ԍ� (thinking_number)
  
  MonAPI::Date date;
  date.refresh();
  rand.setSeed(date.hour() * 3600 + date.min() * 60 + date.sec());
  
  this->offset = Point::get_Empty();
  this->set_ClientSize(Size(KUKURI_WIDTH, KUKURI_HEIGHT));
  
  _P<MonAPI::Screen> scr = GetDefaultScreen();
  this->set_Location(Point(
    (scr->getWidth () - KUKURI_WIDTH ) / 2,
    (scr->getHeight() - KUKURI_HEIGHT) / 2));
  
  this->set_TransparencyKey(KUKURI_NONE);
  this->set_Text("�N�N���l");
  
  this->timer = new Timer();
  this->timer->set_Interval(100);
  this->timer->add_Tick(new EventHandler<Kukuri>(this, &Kukuri::timer_Tick));
  
  setBitmaps();
}


/**
  �E���玞�v���ɂ�����Ɖ�鏇��
*/

void Kukuri::setBitmaps()
{
  String bundlePath = MonAPI::System::getBundlePath();
  this->kukuri = new Bitmap(bundlePath + "/KUKURI.BM2");
  
  int w = this->kukuri->get_Width(), h = this->kukuri->get_Height();
  this->kukuriMirror = new Bitmap(w, h);
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
      this->kukuriMirror->SetPixel(x, y, this->kukuri->GetPixel(w - x - 1, y));
    }
  }
  
  // �����Ă���Ƃ��̉摜
  kuPix[ 0] = kukuri_r  ;  // �E   1
  kuPix[ 1] = kukuri_fr ;  // �E�� 1
  kuPix[ 2] = kukuri_f  ;  // �@�� 1
  kuPix[ 6] = kukuri_b  ;  // �@�� 1
  kuPix[ 7] = kukuri_br ;  // �E�� 1
  kuPix[ 8] = kukuri_r2 ;  // �E   2
  kuPix[ 9] = kukuri_fr2;  // �E�� 2
  kuPix[10] = kukuri_f2 ;  // �@�� 2
  kuPix[14] = kukuri_b2 ;  // �@�� 2
  kuPix[15] = kukuri_br2;  // �E�� 2
  kuPix[24] = kukuri_r3 ;  // �E   3
  kuPix[25] = kukuri_fr3;  // �E�� 3
  kuPix[31] = kukuri_br3;  // �E�� 3
  kuPix[ 3] = kuPix[ 1] + MIRROR; // ���� 1
  kuPix[ 4] = kuPix[ 0] + MIRROR; // ��   1
  kuPix[ 5] = kuPix[ 7] + MIRROR; // ���� 1
  kuPix[11] = kuPix[ 9] + MIRROR; // ���� 2
  kuPix[12] = kuPix[ 8] + MIRROR; // ��   2
  kuPix[13] = kuPix[15] + MIRROR; // ���� 2
  kuPix[26] = kuPix[10] + MIRROR; // �@�� 2
  kuPix[27] = kuPix[25] + MIRROR; // ���� 3
  kuPix[28] = kuPix[24] + MIRROR; // ��   3
  kuPix[29] = kuPix[31] + MIRROR; // ���� 3
  kuPix[30] = kuPix[14] + MIRROR; // �@�� 2
  
  kuTurn[ 0] = kukuri_turn_f ; // �@��
  kuTurn[ 4] = kukuri_turn_b ; // �@��
  kuTurn[ 5] = kukuri_turn_br; // �E��
  kuTurn[ 6] = kukuri_turn_r ; // �E
  kuTurn[ 7] = kukuri_turn_fr; // �E��
  kuTurn[ 8] = kukuri_turn_f ; // �@��
  kuTurn[10] = kukuri_turn_r2; // �E��
  kuTurn[ 1] = kuTurn[ 7] + MIRROR;   // ����
  kuTurn[ 2] = kuTurn[ 6] + MIRROR;   // ��
  kuTurn[ 3] = kuTurn[ 5] + MIRROR;   // ����
  kuTurn[ 9] = kuTurn[10] + MIRROR;   // ����
  
  // ��������
  kuSleep[0] = kukuri_sl1; 
  kuSleep[1] = kukuri_sl2;
  
  // �΂��΂�
  kuBye[0] = kukuri_bye_1;
  kuBye[1] = kukuri_bye_2;
  kuBye[2] = kukuri_bye_3;
  kuBye[3] = kukuri_bye_4;
  
  // ���b�I
  kuWow[1] = kukuri_wow;
  kuWow[0] = kuWow[1] + MIRROR;
  
  //���ق͋�
  kuThink[0] = kukuri_th1;
  kuThink[1] = kukuri_th2;
  kuThink[2] = kukuri_th3;
  kuThink[3] = kukuri_th4;
}


Kukuri::~Kukuri()
{
}


void Kukuri::Create()
{
  Form::Create();
  this->timer->Start();
}


void Kukuri::Dispose()
{
  this->timer->Dispose();
  this->kukuri->Dispose();
  this->kukuriMirror->Dispose();
  Form::Dispose();
}


/**
  ���̊֐��͒��ڌĂ�ł͂����Ȃ��B
  �K��Refresh()�ɂ��ԐړI�ɌĂԂ��ƁB
*/

void Kukuri::OnPaint()
{
  _P<Graphics> g = this->CreateGraphics();
  g->DrawImage(this->nowPix < MIRROR ? this->kukuri : this->kukuriMirror,
    0, 0 - KUKURI_HEIGHT * (this->nowPix % MIRROR));
  g->Dispose();
  
  // �őO�ʂɈړ�
  MonAPI::Message::send(__gui_server, MSG_GUISERVER_WINDOWTOFRONTMOST, this->get_Handle());
}


Control::NCState Kukuri::NCHitTest(int x, int y)
{
  return NCState_TitleBar;
}


void Kukuri::OnNCMouseDown(_P<MouseEventArgs> e)
{
  if (e->Button != 2) Form::OnNCMouseDown(e);
}


void Kukuri::OnNCMouseUp(_P<MouseEventArgs> e)
{
  int x = e->X + this->offset.X, y = e->Y + this->offset.Y;
  if (e->Button == 2 && 0 <= x && x < this->get_Width() && 0 <= y && y < this->get_Height())
  {
     if (this->n_state != 6) this->n_state = 6;
  }
  else
  {
    Form::OnNCMouseUp(e);
  }
}


/**
  �^�C�}�[
*/

void Kukuri::timer_Tick(_P<Object> sender, _P<EventArgs> e)
{
  this->nowCount++;
  if (this->nowCount < this->count) return;
  
  this->nowCount = 0;
  this->count = 2;
  
  switch(this->n_state){
  case 1:  // ���ʂ̎�
    this->normal();
    break;
  case 2:  // ���������B
    this->sleeping();
    break;
  case 3:  // ���邭��B
  case 4:  // ���j���[�ҏW
  case 5:  // About�\��
    count = 1;
    this->turn();
    break;
  case 7:  // ���s����
    this->turn();
    break;
  case 6:  // �΂��΂�
    count = 4;
    this->byebye();
    break;
  case 8:  // �т�����
    this->wow();
    break;
  case 9:  // ���胂�[�h
    //this->self();
    break;
  default: // ����B���Ƃ��B
    this->Hide();
    Application::Exit();
    return;
  }
}


/**
  �ʏ�̏��(�ǂ�������)
*/

void Kukuri::normal()
{
  /** �Â����� */
  int old_d = 0;
  int w_tmp = 0;
  
  Point mp = Cursor::get_Position();
  this->calculation(mp.X, mp.Y);
  
  if(distance > 16){    // �߂�����Ƃ��͌�����ς��Ȃ�
    old_d = d;          //360�x��8���������45�x�Ȃ̂ŁA
    d = int((r+22)/45); //22.5�x����45�x���Ō��������߂�B
    if(d > 7) d -= 8;
  }
  
  // w_num=0, 2 �͋C��t���B1 �͉E��, 3 �͍������O�B
  // 2 �̂Ƃ��� w_tmp = 0 ���|���ă`�����ɂ���
  if(w_num == 2) w_tmp = 0; else w_tmp = 1;
  nowPix = kuPix[d + (8 * w_num) * w_tmp];
  
  // ������70�ȏ�̎�����������
  if(distance > 70){
    if(w_num == 3) w_num = 0; else w_num++;
    this->set_Location(Point((int)(this->get_X() + px), (int)(this->get_Y() + py)));
    s_interval = 0;
  }
  this->Refresh();
}


/**
  �ʒu�̌v�Z
  
  �摜�̒��S����v�Z����悤�ɕ␳�B
*/

void Kukuri::calculation(int tmp_x, int tmp_y)
{
  double tx = tmp_x - (this->get_X() + KUKURI_WIDTH  / 2);
  double ty = tmp_y - (this->get_Y() + KUKURI_HEIGHT / 2);
  distance = sqrt(tx * tx + ty * ty);
  /** �p�x�i���W�A���j */
  double rr = atan2(tx, ty);
  
  r = int(DEG(rr));
  
  px = IDOU * cos(rr);
  py = IDOU * sin(rr);
}


/**
  ���]���ĉ��ɂ����
*/

void Kukuri::turn()
{
  int t = 0;
  
  if(t_num < 9){  // ��] Pixmap ��9��
    nowPix = kuTurn[t_num];
    t_num++;
    this->Refresh();
    return;
  }
  
  if(a_t_num == 11){  // �ړ����I��,���������
    t_num = a_t_num = 0;
    switch(n_state){  // �������炻�ꂼ����s
    //case 4:  editMenu();n_state=1;break;
    //case 5:  about(0, 0);break;
    //case 7:  generate();          break;
    default:
      n_state = 1;
    }
    a_t_dir = 0;
    return;
  }else if(a_t_num > 6){  // �ړ������I�����Ă�������
    switch(a_t_num){  // ���n�I�ȏ���
    case 7:
    case 10:
      if(a_t_dir2) t = 2; else t = 6;
      break;
    case 8:
    case 9:
      if(a_t_dir2) t = 9; else t = 10;
      break;
    default:
      this->Hide();
      Application::Exit();
      return;
    }
    nowPix = kuTurn[t];
    a_t_num++;
  }else{  // ���ɂ����
    if(a_t_dir == 0){  // ���߂Ă������珈��
      a_t_dir= 1; a_t_dir2=1; // �������ŉE�ړ�
    }
    switch(a_t_num){  // ���n�I�ȏ���
    case 0:
    case 4:
    case 2:
    case 6:
      t = 0;
      break;
    case 1:
    case 5:
      t = 8;
      break;
    case 3:
    case 7:
      t = 24;
      break;
    default:
      this->Hide();
      Application::Exit();
      return;
    }
    nowPix = kuPix[t + a_t_dir2 * 4];
    this->set_Location(Point(this->get_X() + (a_t_dir * 4), this->get_Y()));
    a_t_num++;
  }
  this->Refresh();
}


/**
  �N�N���l�˂ނ˂�
*/

void Kukuri::sleeping()
{
  // 10�J�E���g�ł������肷��
  if(s_count != 10){
    s_count++;  // �J�E���g����
    return;
  }
  
  s_pixmap = !s_pixmap; // 0, 1 �� Pixmap����ꊷ��
  nowPix = kuSleep[s_pixmap];
  s_count = 0;
  
  // �����������[�h�Ȃ�N���邩�ǂ�������
  if(a_state == 3 && (int)(rand.nextDouble() * 10) == 0){
    n_state = 9;
    a_state = 0;
  }
}


/**
  �΂��΁[��
*/

void Kukuri::byebye()
{
  if(t_num >= 8){
    this->Hide();
    Application::Exit();
    return;
  }
  
  switch(t_num){
  case 4:   // ���n�I�� Pixmap������
  case 6:
  case 8:
    nowPix = kuBye[2];
    break;
  case 5:
  case 7:
    nowPix = kuBye[3];
    break;
  default:
    nowPix = kuBye[t_num];
  }
  this->Refresh();
  t_num++;
}


/**
  �т�����
*/

void Kukuri::wow()
{
  int t = 0;
  
  // turn() �̒��ɓ����ƁA
  // turn() ���I������玟�����s�����̂�
  // �т����肪�I����Ă��� ���s����������Ă��܂�
  // �s���������̂ŕʂɂ��Ă���
  
  if(t_num < 13){  // �т�����̃J�E���g��
    if(a_t_dir2) t = 0; else t = 1; // Pixmap����
    nowPix = kuWow[t];
    t_num++;
  }else{  // �J�E���g���I�������
    nowPix = kuPix[d];
    t_num = 0;
    if(a_state == 2){
      // �������[�h�ŗ����ꍇ�̏���
      n_state = 9;
      a_state = 0;
    }else{
      n_state = 1;
    }
  }
  this->Refresh();
}

void Kukuri::Main(_A<String> args)
{
    _P<Kukuri> kukuri = new Kukuri();
    Application::Run(kukuri.get());
    kukuri->Dispose();
}

SET_MAIN_CLASS(Kukuri)
