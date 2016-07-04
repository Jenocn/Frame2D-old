#include "EventDispatcher.h"
#include "Listener.h"

USING_NS_F2D

static EventDispatcher* pInstance = 0;

EventDispatcher* EventDispatcher::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new EventDispatcher();
	}

	return pInstance;
}

void EventDispatcher::Release()
{
	Clear();

	delete this;
	pInstance = 0;
}

void EventDispatcher::Notify(const MSG& msg)
{
	switch (msg.message)
	{
	case WM_KEYDOWN:
		_msgInfo.message = F2D_MESSAGE_KEYDOWN;
		break;
	case WM_KEYUP:
		_msgInfo.message = F2D_MESSAGE_KEYUP;
		break;
	case WM_LBUTTONDOWN:
		_msgInfo.message = F2D_MESSAGE_LBUTTONDOWN;
		break;
	case WM_LBUTTONUP:
		_msgInfo.message = F2D_MESSAGE_LBUTTONUP;
		break;
	case WM_RBUTTONDOWN:
		_msgInfo.message = F2D_MESSAGE_RBUTTONDOWN;
		break;
	case WM_RBUTTONUP:
		_msgInfo.message = F2D_MESSAGE_RBUTTONUP;
		break;
	default:
		_msgInfo.message = F2D_MESSAGE_NULL;
		break;
	}

	switch (msg.wParam)
	{
	case VK_UP:
		_msgInfo.keycode = F2D_KEYCODE_UP;
		break;
	case VK_DOWN:
		_msgInfo.keycode = F2D_KEYCODE_DOWN;
		break;
	case VK_LEFT:
		_msgInfo.keycode = F2D_KEYCODE_LEFT;
		break;
	case VK_RIGHT:
		_msgInfo.keycode = F2D_KEYCODE_RIGHT;
		break;
	case 'A':
		_msgInfo.keycode = F2D_KEYCODE_A;
		break;
	case 'B':
		_msgInfo.keycode = F2D_KEYCODE_B;
		break;
	case 'C':
		_msgInfo.keycode = F2D_KEYCODE_C;
		break;
	case 'D':
		_msgInfo.keycode = F2D_KEYCODE_D;
		break;
	case 'E':
		_msgInfo.keycode = F2D_KEYCODE_E;
		break;
	case 'F':
		_msgInfo.keycode = F2D_KEYCODE_F;
		break;
	case 'G':
		_msgInfo.keycode = F2D_KEYCODE_G;
		break;
	case 'H':
		_msgInfo.keycode = F2D_KEYCODE_H;
		break;
	case 'I':
		_msgInfo.keycode = F2D_KEYCODE_I;
		break;
	case 'J':
		_msgInfo.keycode = F2D_KEYCODE_J;
		break;
	case 'K':
		_msgInfo.keycode = F2D_KEYCODE_K;
		break;
	case 'L':
		_msgInfo.keycode = F2D_KEYCODE_L;
		break;
	case 'M':
		_msgInfo.keycode = F2D_KEYCODE_M;
		break;
	case 'N':
		_msgInfo.keycode = F2D_KEYCODE_N;
		break;
	case 'O':
		_msgInfo.keycode = F2D_KEYCODE_O;
		break;
	case 'P':
		_msgInfo.keycode = F2D_KEYCODE_P;
		break;
	case 'Q':
		_msgInfo.keycode = F2D_KEYCODE_Q;
		break;
	case 'R':
		_msgInfo.keycode = F2D_KEYCODE_R;
		break;
	case 'S':
		_msgInfo.keycode = F2D_KEYCODE_S;
		break;
	case 'T':
		_msgInfo.keycode = F2D_KEYCODE_T;
		break;
	case 'U':
		_msgInfo.keycode = F2D_KEYCODE_U;
		break;
	case 'V':
		_msgInfo.keycode = F2D_KEYCODE_V;
		break;
	case 'W':
		_msgInfo.keycode = F2D_KEYCODE_W;
		break;
	case 'X':
		_msgInfo.keycode = F2D_KEYCODE_X;
		break;
	case 'Y':
		_msgInfo.keycode = F2D_KEYCODE_Y;
		break;
	case 'Z':
		_msgInfo.keycode = F2D_KEYCODE_Z;
		break;
	case VK_ESCAPE:
		_msgInfo.keycode = F2D_KEYCODE_ESC;
		break;
	case VK_LCONTROL:
		_msgInfo.keycode = F2D_KEYCODE_CTRLL;
		break;
	case VK_RCONTROL:
		_msgInfo.keycode = F2D_KEYCODE_CTRLR;
		break;
	case VK_LSHIFT:
		_msgInfo.keycode = F2D_KEYCODE_SHIFTL;
		break;
	case VK_RSHIFT:
		_msgInfo.keycode = F2D_KEYCODE_SHIFTR;
		break;
	case VK_LMENU:
		_msgInfo.keycode = F2D_KEYCODE_ALTL;
		break;
	case VK_RMENU:
		_msgInfo.keycode = F2D_KEYCODE_ALTR;
		break;
	case VK_SPACE:
		_msgInfo.keycode = F2D_KEYCODE_SPACE;
		break;
	case VK_RETURN:
		_msgInfo.keycode = F2D_KEYCODE_ENTER;
		break;
	case VK_BACK:
		_msgInfo.keycode = F2D_KEYCODE_BACKSPACE;
		break;
	case VK_TAB:
		_msgInfo.keycode = F2D_KEYCODE_TAB;
		break;
	case VK_F1:
		_msgInfo.keycode = F2D_KEYCODE_F1;
		break;
	case VK_F2:
		_msgInfo.keycode = F2D_KEYCODE_F2;
		break;
	case VK_F3:
		_msgInfo.keycode = F2D_KEYCODE_F3;
		break;
	case VK_F4:
		_msgInfo.keycode = F2D_KEYCODE_F4;
		break;
	case VK_F5:
		_msgInfo.keycode = F2D_KEYCODE_F5;
		break;
	case VK_F6:
		_msgInfo.keycode = F2D_KEYCODE_F6;
		break;
	case VK_F7:
		_msgInfo.keycode = F2D_KEYCODE_F7;
		break;
	case VK_F8:
		_msgInfo.keycode = F2D_KEYCODE_F8;
		break;
	case VK_F9:
		_msgInfo.keycode = F2D_KEYCODE_F9;
		break;
	case VK_F10:
		_msgInfo.keycode = F2D_KEYCODE_F10;
		break;
	case VK_F11:
		_msgInfo.keycode = F2D_KEYCODE_F11;
		break;
	case VK_F12:
		_msgInfo.keycode = F2D_KEYCODE_F12;
		break;
	case VK_NUMPAD0:
		_msgInfo.keycode = F2D_KEYCODE_NUM0;
		break;
	case VK_NUMPAD1:
		_msgInfo.keycode = F2D_KEYCODE_NUM1;
		break;
	case VK_NUMPAD2:
		_msgInfo.keycode = F2D_KEYCODE_NUM2;
		break;
	case VK_NUMPAD3:
		_msgInfo.keycode = F2D_KEYCODE_NUM3;
		break;
	case VK_NUMPAD4:
		_msgInfo.keycode = F2D_KEYCODE_NUM4;
		break;
	case VK_NUMPAD5:
		_msgInfo.keycode = F2D_KEYCODE_NUM5;
		break;
	case VK_NUMPAD6:
		_msgInfo.keycode = F2D_KEYCODE_NUM6;
		break;
	case VK_NUMPAD7:
		_msgInfo.keycode = F2D_KEYCODE_NUM7;
		break;
	case VK_NUMPAD8:
		_msgInfo.keycode = F2D_KEYCODE_NUM8;
		break;
	case VK_NUMPAD9:
		_msgInfo.keycode = F2D_KEYCODE_NUM9;
		break;
	case '0':
		_msgInfo.keycode = F2D_KEYCODE_0;
		break;
	case '1':
		_msgInfo.keycode = F2D_KEYCODE_1;
		break;
	case '2':
		_msgInfo.keycode = F2D_KEYCODE_2;
		break;
	case '3':
		_msgInfo.keycode = F2D_KEYCODE_3;
		break;
	case '4':
		_msgInfo.keycode = F2D_KEYCODE_4;
		break;
	case '5':
		_msgInfo.keycode = F2D_KEYCODE_5;
		break;
	case '6':
		_msgInfo.keycode = F2D_KEYCODE_6;
		break;
	case '7':
		_msgInfo.keycode = F2D_KEYCODE_7;
		break;
	case '8':
		_msgInfo.keycode = F2D_KEYCODE_8;
		break;
	case '9':
		_msgInfo.keycode = F2D_KEYCODE_9;
		break;
	case VK_HOME:
		_msgInfo.keycode = F2D_KEYCODE_HOME;
		break;
	case VK_END:
		_msgInfo.keycode = F2D_KEYCODE_END;
		break;
	case VK_INSERT:
		_msgInfo.keycode = F2D_KEYCODE_INSERT;
		break;
	case VK_DELETE:
		_msgInfo.keycode = F2D_KEYCODE_DELETE;
		break;
	case VK_PRIOR:
		_msgInfo.keycode = F2D_KEYCODE_PAGEUP;
		break;
	case VK_NEXT:
		_msgInfo.keycode = F2D_KEYCODE_PAGEDOWN;
		break;
	case VK_CAPITAL:
		_msgInfo.keycode = F2D_KEYCODE_CAPSLOCK;
		break;
	case VK_ADD:
		_msgInfo.keycode = F2D_KEYCODE_NUM_ADD;
		break;
	case VK_SUBTRACT:
		_msgInfo.keycode = F2D_KEYCODE_NUM_MINUS;
		break;
	case VK_MULTIPLY:
		_msgInfo.keycode = F2D_KEYCODE_NUM_MULTIPLY;
		break;
	case VK_DIVIDE:
		_msgInfo.keycode = F2D_KEYCODE_NUM_DIVIDE;
		break;
	case VK_DECIMAL:
		_msgInfo.keycode = F2D_KEYCODE_NUM_POINT;
		break;
	default:
		_msgInfo.keycode = F2D_KEYCODE_NULL;
		break;
	}

	_msgInfo.positionX = LOWORD(msg.lParam);
	_msgInfo.positionY = HIWORD(msg.lParam);

	//vector<Listener*>::iterator ite = m_listener_list.begin();
	//while (ite != m_listener_list.end())
	//{
	//	if ((*ite)->IsVisible() == false)
	//	{
	//		(*ite)->Release();
	//		ite = m_listener_list.erase(ite);
	//	}
	//	else
	//	{
	//		++ite;
	//	}
	//}

	for (int i = 0; i < m_listener_list.size(); ++i)
	{
		m_listener_list.at(i)->Notify(_msgInfo);
	}
}

void EventDispatcher::Add(Listener* listener)
{
	m_listener_list.push_back(listener);
}

void EventDispatcher::Remove(Listener* listener)
{
	vector<Listener*>::iterator ite = m_listener_list.begin();
	while (ite != m_listener_list.end())
	{
		if ((*ite) == listener)
		{
			(*ite)->Release();
			m_listener_list.erase(ite);
			break;
		}

		++ite;
	}
}

void EventDispatcher::RemoveByEventObj(EventObj* obj)
{
	vector<Listener*>::iterator ite = m_listener_list.begin();
	while (ite != m_listener_list.end())
	{
		if ((*ite)->GetEventObj() == obj)
		{
			(*ite)->Release();
			m_listener_list.erase(ite);
			//(*ite)->SetVisible(false);
			break;
		}

		++ite;
	}
}

void EventDispatcher::Clear()
{
	vector<Listener*>::iterator ite = m_listener_list.begin();
	while (ite != m_listener_list.end())
	{
		(*ite)->Release();
		ite = m_listener_list.erase(ite);
	}
}
