#include<userlib.h>
#include<OthelloBoard.h>

/*----------------------------------------------------------------------
    Mona�A�v���P�[�V����
----------------------------------------------------------------------*/
class myApplication : public MonaApplication, public Observer {

  public:
    myApplication(char* name);
    virtual ~myApplication() {}

  public:
    virtual int main(List<char*>* pekoe);
    virtual void onKeyDown(int keycode, int modifiers);
    virtual void onMouseClick(int x, int y);
    virtual void update(Observable* o, void* arg);

  public:
    virtual void init();
    virtual void drawBoard();
    virtual void drawPieces(int x, int y);

  public:
    static const int PIECE_SIZE = 40;

  protected:
    OthelloBoard* board;
    Screen* virtualScreen;
    Screen screen;

};

/*----------------------------------------------------------------------
    Main�֐�
----------------------------------------------------------------------*/
int MonaMain(List<char*>* pekoe) {

    monaApp = new myApplication("OTHELLO.ELF");
    monaApp->main(pekoe);
    monaApp->onMouseClick(5, 5);
    return 0;
}

/*----------------------------------------------------------------------
    myApplication
----------------------------------------------------------------------*/

// �R���X�g���N�^
myApplication::myApplication(char* name) : MonaApplication(name) {
}

// main
int myApplication::main(List<char*>* pekoe) {

    // ��������
    init();

    // �I�Z���̏�����Ԃ�`��
    drawBoard();

    // �C�x���g��҂�
    for (;;);
    return 0;
}

// �I�Z����`��
void myApplication::drawBoard() {

    for (int x = 0; x < OthelloBoard::BOARDW; x++) {
        for (int y = 0; y < OthelloBoard::BOARDH; y++) {
            drawPieces(x, y);
        }
    }
}

// (x, y)�ɂЂƂ��ܕ`��
void myApplication::drawPieces(int x, int y) {

    int piece = this->board->getPiece(x, y);
    int s = PIECE_SIZE;

    // ���o�b�t�@�����VRAM�ɓ]��
    switch(piece) {

    case(OthelloBoard::BLACK):
        Screen::bitblt(&screen, x * s, y * s, s, s, virtualScreen, 0, 0);
        break;
    case(OthelloBoard::WHITE):
        Screen::bitblt(&screen, x * s, y * s, s, s, virtualScreen, s, 0);
        break;
    case(OthelloBoard::EMPTY):
        Screen::bitblt(&screen, x * s, y * s, s, s, virtualScreen, 2 * s, 0);
        break;
    default:
        break;
    }
}

// �L�[���͂͂��Ȃ�
void myApplication::onKeyDown(int keycode, int modifiers) {
}

// �}�E�X�N���b�N�C�x���g
void myApplication::onMouseClick(int x, int y) {

    // �I�Z���̂ǂ����N���b�N���ꂽ
    int bx = (x - x % PIECE_SIZE) / PIECE_SIZE;
    int by = (y - y % PIECE_SIZE) / PIECE_SIZE;

    // �͈̓`�F�b�N
    if (!board->checkRange(bx, by)) {
        return;
    }

    // ���݂̃v���C���[�����܂�����
    int current = board->getCurrentHand();
    if (!(board->setPiece(bx, by, current))) {
        return;
    }

    // �Ђ�����Ԃ���邱�܂��ꖇ���`��
    while (board->existNotReversedPieces()) {

        board->reverseNext();
    }
}

// �I�Z���̓��e�ɕύX�����������Ƃ����̊֐��ɒʒm�����
void myApplication::update(Observable* o, void* arg) {

    if (arg == NULL) {
        drawBoard();
    } else {

        Point* point = (Point*)arg;
        drawPieces(point->x, point->y);
    }
}

void myApplication::init() {

    // �}�E�X�T�[�o�[�Ǝ������g��PID�𓾂�
    dword myPid   = Message::lookup("OTHELLO.ELF");
    dword destPid = Message::lookup("MOUSE.SVR");

    // �}�E�X�T�[�o�͋N�����Ă���H
    if (destPid == 0) {
        printf("process MOUSE.SVR not found\n");
        exit(-1);
    }

    // �}�E�X�T�[�o�[�Ƀ}�E�X���������悤�Ɏ������g��o�^���郁�b�Z�[�W�𑗐M 
    MessageInfo info;
    Message::create(&info, MSG_MOUSE_REGIST_TO_SERVER, myPid, 0, 0, NULL);
    if (Message::send(destPid, &info)) {
        printf("regist error\n");
    }

    // �I�Z���𐶐�
    this->board = new OthelloBoard();

    // �I�Z���ɕύX����������ʒm���Ă��炤
    this->board->addObserver(this);

    // ���o�b�t�@�p�ɉ��z�X�N���[�����m��
    virtualScreen = new VirtualScreen(200 * 1024);

    // �`�敔�i�Ƃ��Ĕ��ہE���ہE��̕��i�𗠃o�b�t�@�ɕ`��
    int s = PIECE_SIZE;
    int s1 = (int)(0.5 * s);
    virtualScreen->fillRect16(0, 0, s, s, Color::rgb(0x00, 0xFF, 0x00));
    virtualScreen->fillRect16(s , 0, s, s, Color::rgb(0x00, 0xFF, 0x00));
    virtualScreen->fillCircle16(s1 * 3, s1, s1 - 4, Color::rgb(0xFF, 0xFF, 0xFF));
    virtualScreen->fillCircle16(s1, s1, s1 - 4, Color::rgb(0x00, 0x00, 0x00));
    virtualScreen->fillRect16(s * 2, 0, s, s, Color::rgb(0x00, 0xFF, 0x00));

    for (int x = 0; x < 3 * s; x++) {
        virtualScreen->putPixel16(x, s - 1, Color::rgb(0x00, 0x00, 0x00));
    }

    for (int x = 0; x < 3 * s; x++) {
        virtualScreen->putPixel16(x, 0, Color::rgb(0x00, 0x00, 0x00));
    }

    for (int x = 0; x <= 3 * s; x += s) {
        for (int y = 0; y < 3 * s; y++) {
            virtualScreen->putPixel16(x - 1, y, Color::rgb(0x00, 0x00, 0x00));
        }
    }
}

