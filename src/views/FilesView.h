#pragma once

#include <vector>
#if defined(__linux__) || defined(__APPLE__)
#include <limits.h>
#define PATH_MAX_LEN PATH_MAX
#elif _WIN32
#define PATH_MAX_LEN _MAX_PATH
#endif

struct FVFileInfo {
	enum type {
		none,
		file,
		dir
	};
	char *name;
	uint64_t size;
	type fileType;
	void Free();
};

struct FVFileList {
	std::vector<FVFileInfo> files;
	char *filter;
	char *path;
	void ReadDir(const char *full_path, const char *filter = nullptr);
	void Clear();
	void InsertAlphabetically(FVFileInfo& info);

	FVFileList() : filter(nullptr), path(nullptr) {}
};

class FVFileView : protected FVFileList {
public:
	void Draw(const char *title);
	void Show(const char *folder, bool *setWhenDone = nullptr, char *pathWhenDone = nullptr, int pathWhenDoneSize = 0, const char *filter = nullptr);
	void SetSave() { save = true; }
	bool IsOpen() const { return open; }
	const char* GetSelectedFile() const { return selectedFile; }
	FVFileView() : open(false), selected(nullptr), pathTarget(nullptr), pathTargetSize(0), selectIndex(0xffffffff) {
		userPath[0] = 0; userFile[0] = 0; selectedFile[0] = 0;
	}
protected:
	bool Enter(strref newPath);
	bool open;
	bool save;
	bool *selected;
	char *pathTarget;
	int pathTargetSize;
	int selectIndex;
	char userPath[PATH_MAX_LEN];
	char userFile[PATH_MAX_LEN];
	char selectedFile[PATH_MAX_LEN];
};
