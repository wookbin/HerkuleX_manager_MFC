#pragma warning(disable: 4996)


class UseRegistry
{
public:
	UseRegistry(void);
	~UseRegistry(void);
	/*---------------------------------------------------------------------
	레지스트리로 부터 Int형 값을 읽어들이는 함수
	----------------------------------------------------------------------*/
	static UINT RegReadInt( HKEY hKey,
		LPCTSTR lpKey,
		LPCTSTR lpValue,
		INT nDefault )
	{
		HKEY key;
		DWORD dwDisp;
		UINT Result;
		DWORD Size;
		if( RegCreateKeyEx( hKey, lpKey, 0, NULL,
			REG_OPTION_NON_VOLATILE, KEY_READ, NULL,
			&key, &dwDisp ) != ERROR_SUCCESS )
			return 0;
		Size = sizeof( LONG );
		if( RegQueryValueEx( key, lpValue, 0, NULL, (LPBYTE)&Result, &Size ) != ERROR_SUCCESS )
			Result = nDefault;
		RegCloseKey( key );
		return Result;
	}

	/*---------------------------------------------------------------------
	레지스트리로 부터 String형 값을 읽어들이는 함수
	----------------------------------------------------------------------*/
	static BOOL RegReadString( HKEY hKey,
		LPCTSTR lpKey,
		LPCTSTR lpValue,
		LPCTSTR lpDefault,
		LPTSTR lpRet,
		DWORD nSize )
	{
		HKEY key;
		DWORD dwDisp;
		DWORD Size;
		if( RegCreateKeyEx( hKey, lpKey, 0, NULL,
			REG_OPTION_NON_VOLATILE, KEY_READ, NULL,
			&key, &dwDisp ) != ERROR_SUCCESS )
			return FALSE;
		Size = nSize;
		if( RegQueryValueEx( key, lpValue, 0, NULL, (LPBYTE)lpRet, &Size ) != ERROR_SUCCESS )
		{
			strcpy( lpRet, lpDefault );
			return FALSE;
		}
		RegCloseKey( key );
		return TRUE;
	}
	/*---------------------------------------------------------------------
	레지스트리로 Int형 값을 쓰는 함수
	----------------------------------------------------------------------*/
	static BOOL RegWriteInt( HKEY hKey,
		LPCTSTR lpKey,
		LPCTSTR lpValue,
		UINT nData )
	{
		HKEY key;
		DWORD dwDisp;
		if( RegCreateKeyEx( hKey, lpKey, 0, NULL,
			REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL,
			&key, &dwDisp ) != ERROR_SUCCESS )
			return FALSE;
		if( RegSetValueEx( key, lpValue, 0, REG_DWORD, (LPBYTE)&nData, (int)sizeof(UINT) ) != ERROR_SUCCESS )
			return FALSE;
		RegCloseKey( key );
		return TRUE;
	}

	/*---------------------------------------------------------------------
	레지스트리로 String형 값을 쓰는 함수
	----------------------------------------------------------------------*/
	static BOOL RegWriteString( HKEY hKey,
		LPCTSTR lpKey,
		LPCTSTR lpValue,
		LPCTSTR lpData )
	{
		HKEY key;
		DWORD dwDisp;
		if( RegCreateKeyEx( hKey, lpKey, 0, NULL,
			REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL,
			&key, &dwDisp ) != ERROR_SUCCESS )
			return FALSE;
		if( RegSetValueEx( key, lpValue, 0, REG_SZ, (LPBYTE)lpData, (int)strlen( lpData ) + 1 ) != ERROR_SUCCESS )
			return FALSE;
		RegCloseKey( key );
		return TRUE;
	}
	/*---------------------------------------------------------------------
	레지스트리로 Binary형 값을 쓰는 함수
	----------------------------------------------------------------------*/
	static BOOL RegWriteBinary( HKEY hKey,
		LPCTSTR lpKey,
		LPCTSTR lpValue,
		LPCTSTR lpData,
		int size)
	{
		HKEY key;
		DWORD dwDisp;
		if( RegCreateKeyEx( hKey, lpKey, 0, NULL,
			REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL,
			&key, &dwDisp ) != ERROR_SUCCESS )
			return FALSE;
		if( RegSetValueEx( key, lpValue, 0, REG_BINARY, (LPBYTE)lpData, size ) != ERROR_SUCCESS )
			return FALSE;
		RegCloseKey( key );
		return TRUE;
	}
	//레지스트리 삭제함수
	static BOOL RegRemoveValue(HKEY hKey,
		LPCTSTR lpKey,
		LPCTSTR lpValue) {
			HKEY key;
			if( RegOpenKeyEx( hKey, lpKey, 0, KEY_ALL_ACCESS,
				&key) != ERROR_SUCCESS )
				return FALSE;
			if(RegDeleteValue(key, lpValue) != ERROR_SUCCESS)
				return FALSE;
			RegCloseKey( key );
			return TRUE;
	}
};