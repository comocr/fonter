# include <Windows.h>
# include "..\\Utilities\\Config\\ConfigClass.h"
# include "..\\Utilities\\Files\\FilesClass.h"
# include "..\\Utilities\\Image\\ImageClass_0.h" // to inherit

# define FONT_CONFIG_FILE			L"Font.ini"

# define MAX_FILE_NAME_LEN			100
# define MAX_N_SYMBOLS				80
# define BMP_FILE_EXTN				L"bmp"

# define SKIP_N_TOKENS_BEGIN		2
# define SKIP_N_TOKENS_FIRST		1
# define SKIP_N_TOKENS_NBLEAP		2
# define SKIP_N_TOKENS_YBLEAP		4

UINT LoadSymbolNames(const LPWSTR cfgFilePath, LPWSTR*& symbolFileNames);
void Fonter(const LPWSTR symbolFileName);
void Aggregate(const LPWSTR symbolFileName, FilesClass& Files);
