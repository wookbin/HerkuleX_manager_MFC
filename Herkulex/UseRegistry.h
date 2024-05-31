#pragma warning(disable: 4996)


class UseRegistry
{
public:
	UseRegistry(void);
	~UseRegistry(void);
	/*---------------------------------------------------------------------
	������Ʈ���� ���� Int�� ���� �о���̴� �Լ�
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
	������Ʈ���� ���� String�� ���� �о���̴� �Լ�
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
	������Ʈ���� Int�� ���� ���� �Լ�
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
	������Ʈ���� String�� ���� ���� �Լ�
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
	������Ʈ���� Binary�� ���� ���� �Լ�
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
	//������Ʈ�� �����Լ�
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