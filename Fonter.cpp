# include "Fonter.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{

	if(lpCmdLine[0] == L'"')
	{
		UINT i;
		for(i = 0; i < wcslen(lpCmdLine)-1; i++)
			lpCmdLine[i] = lpCmdLine[i+1];
		lpCmdLine[i-1] = NULL;
	}

	LPWSTR* symbolFileName = NULL;
	UINT nSymbols;

	nSymbols = LoadSymbolNames(lpCmdLine, symbolFileName);
	FilesClass::SetFilePathX(lpCmdLine);
	for(UINT iSymbol = 0; iSymbol < nSymbols; iSymbol++)
		Fonter(symbolFileName[iSymbol]);
}

UINT LoadSymbolNames(const LPWSTR cfgFilePath, LPWSTR*& symbolFileName)
{
	ConfigClass Config(cfgFilePath);
	BOOL bLeaping;
	UINT nSymbols;
	Config.AdvanceToken(SKIP_N_TOKENS_BEGIN);
	bLeaping = Config.GetBool();
	nSymbols = Config.GetInt();
	symbolFileName = new LPWSTR[nSymbols];
	Config.AdvanceToken(SKIP_N_TOKENS_FIRST);
	for(UINT iSymbol = 0; ;iSymbol++)
	{
		UINT tokenLen;
		tokenLen = Config.GetTokenLen();
	{
		UINT bufferSz;
		bufferSz = tokenLen+1;
		symbolFileName[iSymbol] = new WCHAR[bufferSz];
		Config.GetString(symbolFileName[iSymbol], bufferSz);
	}
		if(iSymbol == nSymbols-1)
			break;
		else
		{
			UINT aToken;
			if(bLeaping)
				aToken = SKIP_N_TOKENS_YBLEAP;
			else
				aToken = SKIP_N_TOKENS_NBLEAP;
			Config.AdvanceToken(aToken);
		}
	}
	return nSymbols;
}

void Fonter(const LPWSTR symbolFileName)
{
	UINT bufferSz;
	bufferSz = (UINT)wcslen(symbolFileName)+sizeof(L"_*." BMP_FILE_EXTN)+1;
	LPWSTR curFileName = new WCHAR[bufferSz];
	wcscpy_s(curFileName, bufferSz, symbolFileName);
	wcscat_s(curFileName, bufferSz, L"_*." BMP_FILE_EXTN);
	FilesClass Files;
	Files.LoadFileNames(NULL, curFileName);
	Aggregate(symbolFileName, Files);
}

void Aggregate(const LPWSTR symbolFileName, FilesClass& Files)
{
	ImageClass_0 img;
	Files.iFile = 0;
	img.LoadHBMP(Files.CurName(), false);
	Files.iFile = Files.nFiles;
	while(Files.iFile--)
	{
		if(!img.MergeBMP(Files.CurName()))
		{
			MessageBox(NULL, L"Symbol Size Mismatch", Files.CurName(), MB_OK);
			exit(-1);
		}
	}

	UINT bufferSz;
	bufferSz = (UINT)wcslen(symbolFileName)+sizeof(L"." BMP_FILE_EXTN)+1;
	LPWSTR curFileName = new WCHAR[bufferSz];
	wcscpy_s(curFileName, bufferSz, symbolFileName);
	wcscat_s(curFileName, bufferSz, L"." BMP_FILE_EXTN);
	img.Border();
	img.WriteBMP(curFileName, false);
}

//	UINT xWidth = img.width;
//	UINT xHeight = img.height;
