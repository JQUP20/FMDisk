#pragma once
#pragma execution_character_set("utf-8")

// pro_dump.h
// �������ļ�����������������ʱ�Զ�����dump�ļ���
// ���ɵ�dump�ļ��ڳ���Ĺ���Ŀ¼��
// �ļ�����ʽ��:������_ʱ����.dmp
// ʹ��dmpʾ������ֱ�ӰѸ�dmp�ļ�������ͳ�������Ӧ��PDB�ļ�
// ����ͬһ��Ŀ¼�£�Ȼ��˫����dmp�ļ����ɲ鿴�������ֳ�
#pragma once
#include <Windows.h>
#include <tchar.h>
#include <DbgHelp.h>
#include <QDir>
#include <QString>

#pragma comment(lib, "dbghelp.lib")

//����޷��������ⲿ���� __imp_wsprintfW
#pragma comment(lib, "user32.lib")

#ifdef UNICODE
#define TSprintf	wsprintf
#else
#define TSprintf	sprintf
#endif

// �����Զ�����dump�ļ��Ļ���ֻ��Ҫ��main������ʼ��
// ���øú�����EnableAutoDump������
void EnableAutoDump();

// ��������
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException);
void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException);

LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{


    TCHAR szDumpDir[MAX_PATH] = { 0 };
    TCHAR szDumpFile[MAX_PATH] = { 0 };
    TCHAR szMsg[MAX_PATH] = { 0 };
    SYSTEMTIME	stTime = { 0 };

    // ����dump�ļ�·��
    GetLocalTime(&stTime);
    QString path = QDir::toNativeSeparators(QDir::homePath() + "/AppData/Local/FMDisk/Dump");
    path.toWCharArray(szDumpDir);
    //::GetCurrentDirectory(MAX_PATH, szDumpDir);
    TSprintf(szDumpFile, (L"%s\\%04d%02d%02d_%02d%02d%02d.dmp"), szDumpDir,
        stTime.wYear, stTime.wMonth, stTime.wDay,
        stTime.wHour, stTime.wMinute, stTime.wSecond);
    // ����dump�ļ�
    CreateDumpFile(szDumpFile, pException);



    // ���ﵯ��һ������Ի����˳�����
    TSprintf(szMsg, (L"Sorry, masterLocker has crashed, please contact to us for help! \r\ndump file : %s"), szDumpFile);
    FatalAppExit(-1, szMsg);

    return EXCEPTION_EXECUTE_HANDLER;
}

void EnableAutoDump()
{
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
}

// ����Dump�ļ�
void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)
{
    // ����Dump�ļ�
    HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    // Dump��Ϣ
    MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
    dumpInfo.ExceptionPointers = pException;
    dumpInfo.ThreadId = GetCurrentThreadId();
    dumpInfo.ClientPointers = TRUE;

    // д��Dump�ļ�����
    //MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpWithPrivateReadWriteMemory, &dumpInfo, NULL, NULL);
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
    CloseHandle(hDumpFile);
}
