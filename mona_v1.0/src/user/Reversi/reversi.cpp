#include<userlib.h>
#include "ReversiBoard.h"

/*----------------------------------------------------------------------
    Mona���ץꥱ�������
----------------------------------------------------------------------*/
class myApplication : public MonaApplication, public Observer {

  public:
    myApplication();
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
    ReversiBoard* board;
    Screen* virtualScreen;
    Screen screen;

};

/*----------------------------------------------------------------------
    Main�ؿ�
----------------------------------------------------------------------*/
int MonaMain(List<char*>* pekoe) {

    monaApp = new myApplication();
    return monaApp->main(pekoe);
}

/*----------------------------------------------------------------------
    myApplication
----------------------------------------------------------------------*/

// ���󥹥ȥ饯��
myApplication::myApplication() : MonaApplication() {
}

// main
int myApplication::main(List<char*>* pekoe) {

    // �������
    init();

    // �������Ĥν�����֤�����
    drawBoard();

    // ���٥�Ȥ��Ԥ�
    for (;;);
    return 0;
}

// �������Ĥ�����
void myApplication::drawBoard() {

    for (int x = 0; x < ReversiBoard::BOARDW; x++) {
        for (int y = 0; y < ReversiBoard::BOARDH; y++) {
            drawPieces(x, y);
        }
    }
}

// (x, y)�ˤҤȤ�������
void myApplication::drawPieces(int x, int y) {

    int piece = this->board->getPiece(x, y);
    int s = PIECE_SIZE;

    // ΢�Хåե������VRAM��ž��
    switch(piece) {

    case(ReversiBoard::BLACK):
        Screen::bitblt(&screen, x * s, y * s, s, s, virtualScreen, 0, 0);
        break;
    case(ReversiBoard::WHITE):
        Screen::bitblt(&screen, x * s, y * s, s, s, virtualScreen, s, 0);
        break;
    case(ReversiBoard::EMPTY):
        Screen::bitblt(&screen, x * s, y * s, s, s, virtualScreen, 2 * s, 0);
        break;
    default:
        break;
    }
}

// �������ϤϤ��ʤ�
void myApplication::onKeyDown(int keycode, int modifiers) {
}

// �ޥ�������å����٥��
void myApplication::onMouseClick(int x, int y) {

    // �������ĤΤɤ�������å����줿
    int bx = (x - x % PIECE_SIZE) / PIECE_SIZE;
    int by = (y - y % PIECE_SIZE) / PIECE_SIZE;

    // �ϰϥ����å�
    if (!board->checkRange(bx, by)) {
        return;
    }

    // ���ߤΥץ쥤�䡼�����ޤ򤪤�
    int current = board->getCurrentHand();
    if (!(board->setPiece(bx, by, current))) {
        return;
    }

    // �Ҥä����֤���뤳�ޤ���示������
    while (board->existNotReversedPieces()) {

        board->reverseNext();
    }
}

// �������Ĥ����Ƥ��ѹ������ä����Ȥ����δؿ������Τ����
void myApplication::update(Observable* o, void* arg) {

    if (arg == NULL) {
        drawBoard();
    } else {

        Point* point = (Point*)arg;
        drawPieces(point->x, point->y);
    }
}

void myApplication::init() {

    // �ޥ��������С��ȼ�ʬ���Ȥ�PID������
    dword myPid   = System::getPID();
    dword destPid = Message::lookup("MOUSE.SVR");

    // �ޥ��������Фϵ�ư���Ƥ��롩
    if (destPid == 0) {
        printf("process MOUSE.SVR not found\n");
        exit(-1);
    }

    // �ޥ��������С��˥ޥ�������򤯤��褦�˼�ʬ���Ȥ���Ͽ�����å����������� 
    MessageInfo info;
    Message::create(&info, MSG_MOUSE_REGIST_TO_SERVER, myPid, 0, 0, NULL);
    if (Message::send(destPid, &info)) {
        printf("regist error\n");
    }

    // �������Ĥ�����
    this->board = new ReversiBoard();

    // �������Ĥ��ѹ������ä������Τ��Ƥ�餦
    this->board->addObserver(this);

    // ΢�Хåե��Ѥ˲��ۥ����꡼������
    virtualScreen = new VirtualScreen(200 * 1024);

    // �������ʤȤ�����ݡ����ݡ��������ʤ�΢�Хåե�������
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

