#ifndef __Helper_h__
#define __Helper_h__

//=================================================================
//
// ����ƕ֗��ȃ}�N����֐�
//
//=================================================================


#pragma warning(disable:4996)
#include <string>

namespace SimpleLib{

// �x -> ���W�A�� �ϊ�
#define ToRadian(x) ((x)*0.017453f)
// ���W�A�� -> �x �ϊ�
#define ToDegree(x) ((x)*57.3f)

// ���S�ȃ|�C���^�̉��
#define SAFE_FREE(p)		{if(p){free(p);p=nullptr;}}				// malloc�������̂����S��free����}�N��
#define SAFE_RELEASE(p)		{if(p){p->Release();p=nullptr;}}		// COM�I�u�W�F�N�g�n�����S��Release����}�N��
#define SAFE_DELETE(p)		{if(p){delete p;p=nullptr;}}			// new���ꂽ�ϐ������S�ɉ������}�N��
#define SAFE_DELETE_ARRAY(p){if(p){delete[] p;p=nullptr;}}			// new���ꂽ�z������S�ɉ������}�N��

// COM�I�u�W�F�N�g�n�����S��Release����
template<class T>
void Safe_Release(T p)
{
	p->Release();
	p = nullptr;
}
// new���ꂽ�ϐ������S�ɉ������
template<class T>
void Safe_Delete(T p)
{
	delete p;
	p = nullptr;
}
// new���ꂽ�z������S�ɉ������
template<class T>
void Safe_Delete_Array(T p) 
{
	delete[] p; 
	p = nullptr;
}

// �F�֌W�̒Z�k���p
#define XRGB(r,g,b) D3DCOLOR_XRGB(r,g,b)
#define ARGB(a,r,g,b) D3DCOLOR_ARGB(a,r,g,b)
#define RGBA(r,g,b,a) D3DCOLOR_RGBA(r,g,b,a)
#define COLORVALUE(a,r,g,b) D3DCOLOR_COLORVALUE(r,g,b,a)
#define ARGB_FULL D3DCOLOR_ARGB(255,255,255,255)

// FPS�v��
DWORD FpsProc();


// ���O�o��
void AddLogFile(char *LogFileName,char *str, bool bData=false);

//=================================================================
// �ψ������b�Z�[�W�{�b�N�X
//=================================================================
inline void DispMsg(HWND hWnd,char *format, ...)
{
	char str[1024];
	va_list argptr;

	va_start(argptr, format);
	vsprintf(str,format, argptr);
	va_end(argptr);

	MessageBox(hWnd,str,"Message",MB_OK);
}

// �L�[����(1�񉟂�)
bool KeyCheck(int keyCode);


//==========================================================
// �z����O�Ŗ��߂�e���v���[�g�֐�
//	�K�p�������z��@�Ɓ@���̔z��̃T�C�Y�@��������
//	��) int sample[10][10];
//		ArrayZeroClear(&**sample, sizeof(sample));
//==========================================================
template<class T>
bool ArrayZeroClear(T* array, int size) {
	for (int i = 0; i < (size/sizeof(T)); i++) {
		array[i] = 0;
	}
	return true;
}

}


#endif