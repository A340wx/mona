#include <userlib.h>
#include "ReversiBoard.h"

/**
 * ���󥹥ȥ饯��
 */
ReversiBoard::ReversiBoard() {
    init();
}

/**
 * ���ꤵ�줿�����̾�ˤ����Ĥ��뤫�������
 * @param  piece <code>ReversiBoard.WHITE, ReversiBoard.BLACK, ReversiBoard.EMPTY</code>
 * @return ��θĿ�
 */
int ReversiBoard::countPieces(int piece) {

    int result = 0;

    // ��θĿ��������
    for (int x = 0; x < BOARDW; x++) {
        for (int y = 0; y < BOARDH; y++) {
            if (this->board[x][y] == piece) result++;
        }
    }
    return result;
}

/**
 * ���ꤵ�줿���֤ζ���֤�
 * @param  x (x, y) ��ΰ���
 * @param  y (x, y) ��ΰ���
 * @return �� ���̤��ϰϳ��ξ���<code>ReversiBoard.EMPTY</code>
 */
int ReversiBoard::getPiece(int x, int y) {

    // x, y���ϰϤ�����å�
    if (!checkRange(x, y)) return EMPTY;

    // ����֤�
    return board[x][y];
}

/**
 * ���ꤵ�줿���֤ζ���֤�
 * @param  point ��ΰ���
 * @return �� ���̤��ϰϳ��ξ���<code>ReversiBoard.EMPTY</code>
 */
int ReversiBoard::getPiece(Point* point) {
    return getPiece(point->x, point->y);
}

/**
 * ���ߤμ��֤Υץ쥤�䡼���֤�<code>ReversiBoard.EMPTY</code>���֤����Ȥ��Ͼ���η��夬�Ĥ��Ƥ������<BR>
 * @return ���ߤμ��֤Υץ쥤�䡼 <code>ReversiBoard.BLACK, WHITE, EMPTY</code>
 */
int ReversiBoard::getCurrentHand() const {
    return this->currentHand;
}

/**
 * ���ꤵ�줿���֤˶���֤���<BR>
 * ���֤�����硢�֤������򼨤���<BR>
 * <code>Point</code>��notifyObservers��<BR>
 * �ƻ븵�����Τ����
 * @param x (x, y) ��ΰ���
 * @param y (x, y) ��ΰ���
 * @param piece �֤���
 * @return ���֤�����<code>true</code>, ���֤��ʤ��ä���<code>false</code>
 */
bool ReversiBoard::setPiece(int x, int y, int piece) {

    int numReversiblePieces; // ΢�֤����ȤΤǤ�����

    // ���ߤμ�Ⱦȹ�
    if (currentHand != piece) return false;

    // ���꤬�����˽�λ�������ɤ���������å�
    if (existNotReversedPieces()) return false;

    // �������֤��뤫�ɤ�����Ĵ�٤�
    numReversiblePieces = countReversiblePieces(x, y, piece);
    if (numReversiblePieces <= 0) return false;

    // piece��(x, y)���֤����Ȥ��ˡ�΢�֤���򤹤٤Ƶ���
    recordReversiblePieces(x, y, piece);

    // ����֤�
    board[x][y] = piece;

    // ������򵭲�
    allTurns->add(new Point3D(x, y, piece));

    // ����ץ쥤�䡼��Ƚ��
    setNextHand();

    // �ѹ���Observer������
    this->setChanged();
    this->notifyObservers(new Point(x, y));
    this->clearChanged();

    return true;
}

/**
 * <code>setPiece()</code>������ˡ�΢�֤��Ƥʤ���¸�ߤ��뤫���֤�<BR>
 * <pre>
 *    ������ˡ
 *      board.setPiece(3, 5, OthlloBoard::BLACK);
 *      while (existNotReversedPieces()) {
 *          reverseNext();
 *          // �����ѽ���
 *      }
 * </pre>
 * @return ΢�֤��Ƥʤ���¸�ߤ�����<code>true</code>
 */
bool ReversiBoard::existNotReversedPieces() {
    return allNotReversedPieces->size() > 0;
}

/**
 * ���ζ��΢�֤�<BR>
 * ΢�֤������򼨤�<code>Point</code>��notifyObservers�Ǵƻ븵�����Τ����
 * existNotReversedPieces()�λ�����ˡ�򻲾�
 */
void ReversiBoard::reverseNext() {

    // ΢�֤����֤����
    Point* point = allNotReversedPieces->get(0);

    // ΢�֤�
    reversePiece(point->x, point->y);

    // �ѹ�������
    this->setChanged();
    notifyObservers(new Point(point));
    this->clearChanged();

    // ΢�֤����Τǰ��֤�õ�
    allNotReversedPieces->removeAt(0);

    return;
}

/**
 * ���ߥ�������֤�
 * @return ���ߥ�����
 */
int ReversiBoard::getTurn() const {
    return this->turn;
}

/**
 * undo��ǽ
 * 1�����
 */
void ReversiBoard::undo() {

    // 1���������ʤ����
    if (getTurn() < 1) return;

    // ���̽����
    initBoard();

    // �����¤٤ʤ���
    for (int i = 0; i < allTurns->size() -1; i++) {

        // ����֤�
        Point3D* p = allTurns->get(i);
        setPiece(p->x, p->y, p->z);
        while (existNotReversedPieces()) {
            reverseNext();
        }
    }

    // �Ǹ�Υ������õ�
    allTurns->removeAt(allTurns->size() -1);

    return;
}

/**
 * ���ꤵ�줿���֤˶���֤����Ȥ��ˡ������Ķ�΢�֤��뤫���֤�
 * @param x
 * @param y
 * @param piece �֤���
 * @return ΢�֤�����
 */
int ReversiBoard::countReversiblePieces(int x, int y, int piece) {

    int result = 0;

    // x, y���ϰϤ�����å�
    if (!checkRange(x, y)) return 0;

    // ���Ǥ˶��֤���Ƥ��뤫������å�
    if (board[x][y] != EMPTY) return 0;

    // (x, y)��piece���֤�������΢�֤����ȤΤǤ�����8������õ��
    result += countReversiblePieceToOneAngle(x, y,  1,  0, piece, false);
    result += countReversiblePieceToOneAngle(x, y,  1,  1, piece, false);
    result += countReversiblePieceToOneAngle(x, y,  0,  1 ,piece, false);
    result += countReversiblePieceToOneAngle(x, y, -1,  1, piece, false);
    result += countReversiblePieceToOneAngle(x, y, -1,  0, piece, false);
    result += countReversiblePieceToOneAngle(x, y, -1, -1, piece, false);
    result += countReversiblePieceToOneAngle(x, y,  0, -1, piece, false);
    result += countReversiblePieceToOneAngle(x, y,  1, -1, piece, false);

    return result;
}

/**
 * ��С����פ�ꥻ�åȤ���
 */
void ReversiBoard::resetBoard() {

    delete (this->allTurns);
    this->allTurns = new HList<Point3D*>();
    initBoard();

    // �ѹ�������
    this->setChanged();
    this->notifyObservers(NULL);
    this->clearChanged();
    return;
}

/**
 * ReversiBoard�����Ƚ������Ԥ�
 */
void ReversiBoard::init() {

    // ���̽����
    initBoard();

    // ���٤ƤΥ�����򵭲�����Vector�����
    allTurns = new HList<Point3D*>();

    return;
}

/**
 * ���̽�����Ԥ�
 */
void ReversiBoard::initBoard() {

    // ���ߥ����������
    this->turn = 0;

    // ���Ϲ�
    this->currentHand = BLACK;

    // ���̤���ˤ���
    for (int x = 0; x < BOARDW; x++) {
        for (int y = 0; y < BOARDH; y++) board[x][y] = EMPTY;
    }

    // ������֤��֤���Ƥ����򥻥å�
    board[3][3] = BLACK;
    board[4][4] = BLACK;
    board[4][3] = WHITE;
    board[3][4] = WHITE;

    // ΢�֤��٤���Τ��٤ư��֤򵭲�����List�����
    allNotReversedPieces = new HList<Point*>();

    return;
}

/**
 * ���ꤷ�����΢�֤�
 */
void ReversiBoard::reversePiece(int x, int y) {

    // x, y���ϰϤ�����å�
    if (!checkRange(x, y)) return;

    // ���΢�֤����⤷���ʤ鲿�⤷�ʤ�
    board[x][y] = turnColor(board[x][y]);

    return;
}

/**
 * ���Ϥ��줿�ͤ����̾��¸�ߤ��뤫�����å�����
 */
bool ReversiBoard::checkRange(int x, int y) {

    // ���̾�ˤ���Ȥ������
    bool xRange = x >= 0 && x < BOARDW;
    bool yRange = y >= 0 && y < BOARDH;

    // ���̾�ˤ���
    if (xRange && yRange) return true;

    // ���̾�ˤʤ�
    return false;
}

/**
 *  ���ꤵ�줿�٥��ȥ�(toX, toY)��������΢�֤������������
 *  reordFlag��true�λ��ϰ��֤򵭲�
 */
int ReversiBoard::countReversiblePieceToOneAngle(int x, int y, int toX,int toY
                                                 , int piece, bool recordFlag) {
    int result = 0;

    // �٤ζ�ذ�ư
    x += toX;
    y += toY;

    // ���̤�ü�ޤ�õ����³����
    while (x >= 0 && y >= 0 && x < BOARDW && y < BOARDH) {

        // õ����ζ�΢�֤��ο��ʤ�΢�֤���
        if (board[x][y] == turnColor(piece)) {

            // ΢�֤����ΰ��֤򵭲�
            if (recordFlag) allNotReversedPieces->add(new Point(x, y));

            // ������󥯥����
            result++;
        }

        // Ʊ�������ä��顢�����ޤǤ��ä�΢�֤�����΢�֤����Ȥ��Ǥ���
        else if (board[x][y] == piece) return result;

        // ���ʤ�΢�֤��ʤ�
        else if (board[x][y] == EMPTY) {

            if (recordFlag) {

                // �������Ƥ�����ΰ���
                for (int i = 0; i < result; i++) {

                    allNotReversedPieces->removeAt(allNotReversedPieces->size() - 1);
                }
            }
            return 0;
        }

        // ������٤ζ�ذ�ư
        x += toX;
        y += toY;
    }

    if (recordFlag) {

        // �������Ƥ�����ΰ���
        for (int i = 0; i < result; i++) {

            allNotReversedPieces->removeAt(allNotReversedPieces->size() - 1);
        }
    }
    return 0;
}

/**
 * ΢�֤��������֤�
 */
int ReversiBoard::turnColor(int piece) {
    return piece * -1;
}

/**
 * piece��(x, y)���֤����Ȥ��ˡ�΢�֤���򤹤٤Ƶ���
 */
bool ReversiBoard::recordReversiblePieces(int x, int y, int piece) {

    // x, y���ϰϤ�����å�
    if (!checkRange(x, y)) return false;

    // ���Ǥ˶��֤���Ƥ��뤫������å�
    if (board[x][y] != EMPTY) return false;

    // ����ֵ������֥������Ȥ�����
    delete allNotReversedPieces;
    allNotReversedPieces = new HList<Point*>();

    // ΢�֤�����֤򵭲�
    countReversiblePieceToOneAngle(x, y,  1,  0, piece, true);
    countReversiblePieceToOneAngle(x, y,  1,  1, piece, true);
    countReversiblePieceToOneAngle(x, y,  0,  1 ,piece, true);
    countReversiblePieceToOneAngle(x, y, -1,  1, piece, true);
    countReversiblePieceToOneAngle(x, y, -1,  0, piece, true);
    countReversiblePieceToOneAngle(x, y, -1, -1, piece, true);
    countReversiblePieceToOneAngle(x, y,  0, -1, piece, true);
    countReversiblePieceToOneAngle(x, y,  1, -1, piece, true);

    return true;
}

// ����Υץ쥤�䡼��Ƚ��
void ReversiBoard::setNextHand() {

    if (isTherePlace(turnColor(currentHand))) {
        currentHand = turnColor(currentHand);
    } else if (isTherePlace(currentHand)) {

        // ³���Ƥ⤦1��
    } else {

        // ξ�ץ쥤�䡼�����֤���꤬�ʤ�
        currentHand = EMPTY;
    }

    return;
}

// ���̾�˻��ꤵ�줿piece�򤪤����Ȥ��Ǥ��뤫��Ƚ��
bool ReversiBoard::isTherePlace(int piece) {

    int result = 0;

    // ��θĿ��������
    for (int x = 0; x < BOARDW; x++) {
        for (int y = 0; y < BOARDH; y++) {
            result += countReversiblePieces(x, y, piece);
        }
    }

    return result > 0;
}
