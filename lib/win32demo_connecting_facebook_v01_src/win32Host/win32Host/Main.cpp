#include <windows.h>
#include <string>
#include <map>
#include "resource.h" 
#include "fbHalper.h"
//

HBRUSH g_hbrBackground = NULL;
map<std::string,std::string> userMap;
CfbHalper cfbHalper;
 

void settext(HWND hDlg,std::wstring ws,int nIDDlgItem )
{
     
    HWND hWndEdit = GetDlgItem (hDlg,nIDDlgItem);
    
    LPCWSTR pst = ws.c_str();
    int ndx = GetWindowTextLength (hWndEdit);
    SetFocus (hWndEdit);
    #ifdef WIN32
      SendMessage (hWndEdit, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);
    #else
      SendMessage (hWndEdit, EM_SETSEL, 0, MAKELONG (ndx, ndx));
    #endif
      SendMessage (hWndEdit, EM_REPLACESEL,0,(LPARAM)pst);
    
}

void AppendWindowText(HWND hWnd, const char* s)
{
int iLength;
HWND hWndEdit = GetDlgItem (hWnd, IDC_EDIT1);
iLength = GetWindowTextLength(hWndEdit);
SendMessage(hWndEdit, EM_SETSEL, iLength, iLength);
SendMessage(hWndEdit, EM_REPLACESEL, 0, (LPARAM)s);
SendMessage(hWndEdit, WM_VSCROLL, SB_BOTTOM, (LPARAM)NULL);

}

void limitEditText(HWND hWnd,int nIDDlgItem,int from,int to)
{
	HWND hWndEdit = GetDlgItem (hWnd,nIDDlgItem);
	SendMessage (hWndEdit,EM_SETLIMITTEXT,from,to);

}

void setEnable(HWND hWnd,int nIDDlgItem,int state)
{
    
    EnableWindow( GetDlgItem( hWnd, nIDDlgItem ), state);
    

}
BOOL CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:
			g_hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, 
				MAKEINTRESOURCE(IDI_APPLICATION)));
			SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, 
				MAKEINTRESOURCE(IDI_APPLICATION)));
			limitEditText(hwnd,IDC_EDIT3,150,0);
			{
			std::string ss;
            ss.append("Demo of native win32 application showing how 'Like' button can be used from");
            ss.append("\r\n");
            ss.append("desktop apps including games just by loading dll that is responsible for all the work.");
            ss.append("\r\n");
            ss.append("this will allow you to use the demo.");
             ss.append("\r\n");
              ss.append("\r\n");
            ss.append("1.Go to http://www.facebook.com/apps/application.php?id=189927794387507 and press the 'Like'");
            ss.append("\r\n");
            ss.append("to enable the application in your account");
            ss.append("\r\n");
             ss.append("\r\n");
			  ss.append("2.Fill some text in the massage text box .");
            ss.append("\r\n");
             ss.append("\r\n");
            ss.append("3.Press the 'I Like This App' button to popup the Authentication browser.");
            ss.append("\r\n");
             ss.append("\r\n");
            ss.append("4.The buttons will become enabled use one of them to trigger the API's and send requests. ");
            ss.append("\r\n");
             ss.append("\r\n");
             ss.append("\r\n");
            ss.append("If you got any questions please email to:meiry242@gmail.com");
            
            std::wstring str2(ss.length(), L' '); // Make room for characters
             // Copy string to wstring.
            std::copy(ss.begin(), ss.end(), str2.begin()); 
			settext(hwnd,str2,IDC_EDIT2);
			
			
 			settext(hwnd,L"Start Loading fbHalper dll\r\n",IDC_EDIT1);
			settext(hwnd,L"Done fbHalper dll\r\n",IDC_EDIT1);
			 
			}
		break;
		case WM_CLOSE:
			EndDialog(hwnd, 0);
		break;
		case WM_CTLCOLORDLG:	
			//return (LONG)g_hbrBackground;
		case WM_CTLCOLORSTATIC:
		{
			/*HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(255, 255, 255));
			SetBkMode(hdcStatic, TRANSPARENT);
			return (LONG)g_hbrBackground;*/
		}
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
				    
					//MessageBox(NULL, L"IDOK button pressed!", L"Pinky says...", MB_OK | MB_ICONEXCLAMATION);
					{
					settext(hwnd,L"Like button pressed!\r\n",IDC_EDIT1);
					settext(hwnd,L"starting to load Authentication browser component!\r\n",IDC_EDIT1);
					std::string token = cfbHalper.returnToken();
					if(token.size() > 10)
					{
					    settext(hwnd,L"Access token recived!\r\n",IDC_EDIT1);
					    setEnable(hwnd,IDC_BUTTON1,1);
					    setEnable(hwnd,IDC_BUTTON2,1);
					    
					    if(cfbHalper.getUserInfo(userMap))
					    {
					        if(userMap.size() == 0)
					        {
					            settext(hwnd,L"Retriving User Data failed,check fbHelper.log file!\r\n",IDC_EDIT1);
					        }
					        else
					        {
	                             settext(hwnd,L"Retriving User Data succeed \r\n",IDC_EDIT1);	
	                             std::string ss;
	                             ss.append(userMap["id"]);
	                             ss.append(" ");
	                             ss.append(userMap["first_name"]);
	                             ss.append(" ");
	                             ss.append(userMap["last_name"]);
	                             ss.append(" ");
	                             ss.append(userMap["link"]);
	                             ss.append("\r\n");
	                             std::wstring str2(ss.length(), L' '); // Make room for characters
	                             // Copy string to wstring.
                                 std::copy(ss.begin(), ss.end(), str2.begin());
	                             settext(hwnd,str2,IDC_EDIT1);	
	                             
	                             			        
					             
					        }
					    }
					}
					 
 					}
					break;
				case IDC_BUTTON1:
					{
				    
				   
					int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT3));
					if(len > 0)
					{
						 settext(hwnd,L"Sending Hello massage to application wall!\r\n",IDC_EDIT1);
						//char* buf;
						//buf = (char*)GlobalAlloc(GPTR, len + 1);
						TCHAR buffer[1000+1]; 
					    GetDlgItemText(hwnd, IDC_EDIT3, buffer,sizeof(buffer)/sizeof(TCHAR));
						//DWORD iNombreChars = sizeof(buffer)/sizeof(TCHAR);
						size_t size = wcslen(buffer);
						char * buffer1 = new char [2*size+2];
						wcstombs(buffer1,buffer,2*size+2);
						std::string string(buffer1);
						delete [] buffer1;
						//string str="";
 						//str.assign(&buffer[0], &buffer[iNombreChars]);
						//std::wstring w(buffer);
						 
					     
							if(cfbHalper.sendToAppWall(string))
							{
								 settext(hwnd,L"Succesd Sending Check it out at:\r\n\r\nhttp://www.facebook.com/apps/application.php?id=189927794387507&sk=wall\r\n\r\n",IDC_EDIT1);
							}
							else
							{
								settext(hwnd,L"Failed Sending Hello massage to application wall!\r\n",IDC_EDIT1);
							}
						 
					}
					else
					{
						MessageBox(NULL, L"Please write short massage in the text box",L"...", MB_OK | MB_ICONEXCLAMATION);
					}
					
				    break;
					}
				 case IDC_BUTTON2:
				    //MessageBox(NULL, L"IDC_BUTTON1 button pressed!",L"Pinky says...", MB_OK | MB_ICONEXCLAMATION);
					{ 
						
						int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT3));
						if(len > 0)
						{
							settext(hwnd,L"Sending Hello massage to private wall!\r\n",IDC_EDIT1);
							TCHAR buffer[1000+1]; 
							GetDlgItemText(hwnd, IDC_EDIT3, buffer,sizeof(buffer)/sizeof(TCHAR));
							//DWORD iNombreChars = sizeof(buffer)/sizeof(TCHAR);
							//string str="";
							size_t size = wcslen(buffer);
							char * buffer1 = new char [2*size+2];
							wcstombs(buffer1,buffer,2*size+2);
							std::string string(buffer1);
							delete [] buffer1;
							//str.assign(&buffer[0], &buffer[iNombreChars]);
							if(cfbHalper.sendToUserWall(string))
							{

								 std::string ss1;
								 ss1.append("Succesd Sending Check it out at:\r\n\r\n");
								 ss1.append(userMap["link"]);
								 ss1.append("\r\n\r\n");
								 std::wstring str21(ss1.length(), L' '); // Make room for characters
								 // Copy string to wstring.
								 std::copy(ss1.begin(), ss1.end(), str21.begin());
								 settext(hwnd,str21,IDC_EDIT1);	
						         
								// settext(hwnd,L"Succesd Sending Check it out at:\r\nhttp://www.facebook.com/apps/application.php?id=189927794387507&sk=wall\r\n");
							 }
							 else
							 {
								settext(hwnd,L"Failed Sending Hello massage to user wall!\r\n",IDC_EDIT1);
							 }
							 
						}
						else
						{
							MessageBox(NULL, L"Please write short massage in the text box",L"...", MB_OK | MB_ICONEXCLAMATION);
						}
					
				    break;
					}
				break;
			}
		break;
		case WM_DESTROY:
			DeleteObject(g_hbrBackground);
		break;
		default:
			return FALSE;
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}
