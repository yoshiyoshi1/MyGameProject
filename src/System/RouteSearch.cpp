#include "../main.h"
#include "ThreadGuard.h"

#include "RouteSearch.h"

RouteSearch::RouteSearch()
{
	// ���f�[�^
	nextGoalPos.Set(68, 71);
	nextStartPos.Set(1, 1);

	m_meshPin.LoadXFile("../data/Mesh/TestData/pin.x");
}

RouteSearch::~RouteSearch()
{
	// �e���X�g�̃f�[�^���폜����
	mapOpen.clear();
	mapClose.clear();
	
	ResetNodeData();
}

void RouteSearch::Update()
{
	// �J�n�n�_�ƖړI�n���ς���Ă��Ȃ��ꍇ�A�ȍ~�̏������s��Ȃ�
	if (goalPos == nextGoalPos && startPos == nextStartPos)
		return;

	Reset(nextStartPos.x, nextStartPos.y);

	// nextGoalPos �����Ȃ�΁A�V���ȖړI�n�Ƃ��Đݒ�
	if (m_RouteData[nextGoalPos.y][nextGoalPos.x] == 0) {
		goalPos = nextGoalPos;
	}
	// nextGoalPos �����ȊO�Ȃ�΁A�ȍ~�̏������s��Ȃ�
	else {
		return;
	}


	// �o�H�T����ʃX���b�h�ōs��
	std::thread searchThread(&RouteSearch::Search, this);
	ThreadGuard tg(searchThread);	// �G���[�ŗ������ۂɎ�����Join���s��
	searchThread.join();			// �X���b�h�̏I����ҋ@

}

void RouteSearch::Draw()
{
	// �ړI�n�܂ŒT���ł��Ă��邩�m�F
	std::map<int, Node>::iterator itClose = mapClose.find(KEY(goalPos));
	if (itClose == mapClose.end())
		return;

	for (int i = 0; ; i++) {

		// �o�H���s���̃��b�V���ŕ\��
		CMatrix m;
		int blue = (int)(i * (255.0f / (int)mapClose.size()));
		int red = 255 - blue;
		m.CreateMove(itClose->second.pos.x * 2.0f, -3.0f, itClose->second.pos.y * 2.0f);
		m_meshPin.Draw(&m, ARGB_D3DX(255, red, 0, blue));

		// �J�n�n�_�̏ꍇ�A�������I������
		if (itClose->second.pos == startPos)
			return;

		// �C�e���[�^��e�̃m�[�h�ōX�V
		itClose = mapClose.find(KEY(itClose->second.parent->pos));
		if (itClose == mapClose.end())
			return;

	}
}

void RouteSearch::SetMapData(int* mapData)
{
	int i = 0;
	for (int cntY = 0; cntY != SIZE_Y; cntY++) {
		for (int cntX = 0; cntX != SIZE_X; cntX++, i++) {
			m_RouteData[cntY][cntX] = mapData[i];
		}
	}
}

//=======================================================
//	���X�g�����������ăX�^�[�g�n�_���Z�b�g����֐�
//=======================================================
void RouteSearch::Reset(int x, int y)
{
	mapOpen.clear();
	mapClose.clear();
	
	ResetNodeData();

	startPos.Set(x, y);

	Node* pStartNode = &m_NodeData[startPos.y][startPos.x];
	SetNode(
		pStartNode,
		startPos,
		0,
		nullptr
	);
	mapOpen.insert(KEYDATA(startPos, *pStartNode));
}

//=======================================================
//	�m�[�h�f�[�^�����Z�b�g����֐�
//=======================================================
void RouteSearch::ResetNodeData()
{
	for (int cntY = 0; cntY != SIZE_Y; cntY++) {
		for (int cntX = 0; cntX != SIZE_X; cntX++) {
			m_NodeData[cntY][cntX].Reset();
		}
	}
}

//=======================================================
//	�m�[�h�����Z�b�g����֐�
//	@param_out	: node
//=======================================================
void RouteSearch::SetNode(Node* node, Position pos, int score, Node* parentNode)
{
	node->pos = pos;
	node->score = score;
	node->parent = parentNode;
}

//=======================================================
// �w�肵���n�_����S�[���܂ł̋��������߂�i����j
//	@return	: ����
//=======================================================
int RouteSearch::GetDistance(Position fromPos)
{
	// ��Βl�ɏC��
	int x = abs(fromPos.x - goalPos.x);
	int y = abs(fromPos.y - goalPos.y);

	// ����ړ��R�X�g���v�Z �i�΂߁j
	if (x < y) {
		return (x + (y - x));
	}
	else {
		return (y + (x - y));
	}

}

//=======================================================
// �w�肵���n�_����X�^�[�g�n�_�܂ł̋��������߂�
//	@return	: ����
//=======================================================
int RouteSearch::BackTrace(Position pos)
{
	int res = 0;			// ����
	Position tmpPos = pos;	// �L�[�ƂȂ���W

	//------------------------------------------
	// �e��k���Ă����A���������߂�
	//------------------------------------------
	while (true) {
		// �J�n�n�_�܂Ŗ߂����ꍇ�A�������I������
		if (tmpPos == startPos) {
			res++;
			break;
		}

		// Close���X�g����w�肳�ꂽ���W�̃m�[�h��T��
		std::map<int, Node>::iterator it = mapClose.find(KEY(tmpPos));
		if (it == mapClose.end())
			break;
		if (it->second.parent == nullptr)
			break;

		// ���X�g����T���Ă����m�[�h�̐e�̍��W��V���ȍ��W�Ƃ���
		tmpPos = it->second.parent->pos;
		res++;
	}

	return res;
}

//=======================================================
// A*�Ōo�H�T������
//	@return	: �ړI�n�܂ŒT���ł������ǂ���
//=======================================================
bool RouteSearch::Search()
{
	int res = 0;

	while (true) {

		// Open���X�g����Ȃ�T���I���i�S�[���܂ł̓����Ȃ���ԁj
		if (mapOpen.empty()) {
			return false;
		}

		Node* pNode;	// �ŏ��̃R�X�g�����m�[�h�̃|�C���^

		//-----------------------------------------------
		//Open���X�g����ŏ��̃R�X�g�����m�[�h�����o��
		//-----------------------------------------------
		{
			int costMin = 9999;
			std::map<int, Node>::iterator itMin;

			{
				std::map<int, Node>::iterator it = mapOpen.begin();
				while (it != mapOpen.end()) {
					if (costMin > GetDistance(it->second.pos)) {
						costMin = GetDistance(it->second.pos);
						itMin = it;
					}
					it++;
				}
			}

			//m_NodeData[itMin->second.pos.y][itMin->second.pos.x] = itMin->second;
			pNode = &m_NodeData[itMin->second.pos.y][itMin->second.pos.x];

			// Open���X�g����Close���X�g�ֈړ�
			mapClose.insert(KEYDATA(pNode->pos, *pNode));
			mapOpen.erase(KEY(pNode->pos));
		}


		// �ŏ��R�X�g�̃m�[�h����X�^�[�g�܂ł̈ړ��R�X�g
		int backCost = 0;
		backCost = BackTrace(pNode->pos);


		//-----------------------------------------------
		// �㉺���E�̂S�������m�F
		//-----------------------------------------------
		Node* pSubNode;
		int way[4][2] = {
			{  0, -1 },		// ��
			{  1,  0 },		// ��
			{  0,  1 },		// ��
			{ -1,  0 },		// �E
		};

		for (int i = 0; i < 4; i++) {
			// �אڂ���}�X�̍��W���v�Z (�S����)
			Position tmpPos;
			tmpPos.x = pNode->pos.x + way[i][0];
			tmpPos.y = pNode->pos.y + way[i][1];

			// �͈͊O�̏ꍇ�͏������s��Ȃ�
			if (tmpPos.x < 0) continue;
			if (tmpPos.y < 0) continue;
			if (tmpPos.x >= SIZE_X) continue;
			if (tmpPos.y >= SIZE_Y) continue;

			// ���ȊO�̏ꍇ�͏������s��Ȃ�
			if (m_RouteData[tmpPos.y][tmpPos.x] != 0) continue;

			pSubNode = &m_NodeData[tmpPos.y][tmpPos.x];
			SetNode(
				pSubNode,
				tmpPos,
				backCost + GetDistance(tmpPos),	// �X�R�A�i�X�^�[�g�܂ł̋��� + �S�[���܂ł̋����j
				pNode
			);


			//-----------------------------------------------
			//Open���X�g�ɋ��߂����W�Ɠ����m�[�h�����邩�m�F
			//-----------------------------------------------
			if (mapOpen.find(KEY(tmpPos)) != mapOpen.end()) {	// ����ꍇ

				// Open���X�g�ł̃X�R�A��苁�߂��X�R�A�����Ȃ��ꍇ�A�����ς���
				if (pSubNode->score < mapOpen[KEY(tmpPos)].score) {
					mapOpen[KEY(tmpPos)].parent = pNode;
					mapOpen[KEY(tmpPos)].score = pSubNode->score;
				}
				continue;
			}


			//-----------------------------------------------
			//Close���X�g�ɂ��̍��W�Ɠ����m�[�h�����邩�m�F
			//-----------------------------------------------
			if (mapClose.find(KEY(tmpPos)) != mapClose.end()) {	// ����ꍇ

				// Close���X�g�ł̃X�R�A��苁�߂��X�R�A�����Ȃ��ꍇ�A
				//	�V���ȃm�[�h��Open���X�g�ɒǉ���Close���X�g���珜��
				if (pSubNode->score < mapClose[KEY(tmpPos)].score) {
					Node tmp;
					SetNode(
						&tmp,
						tmpPos,
						pSubNode->score,
						pNode
					);

					mapOpen.insert(KEYDATA(tmpPos, tmp));
					mapClose.erase(KEY(tmpPos));
				}
				continue;
			}

			// ������Ȃ���ΐV�K�Ƃ���Open���X�g�֒ǉ�
			mapOpen.insert(KEYDATA(pSubNode->pos, *pSubNode));
		}

		//-----------------------------------------------
		//����������T���I��
		//-----------------------------------------------
		if (pNode->pos == goalPos) {
			return true;
		}

		// ������Ȃ������������x�T��
	}
}
