#ifndef _DISK_H_
#define _DISK_H_

#include "Imenik.h"

class Disk {
	Imenik* koren;
	void Copy(const Disk&);
	void Move(Disk&);
	void Delete();
public:
	Disk();
	Disk(const Disk&);
	Disk(Disk&&);
	~Disk();

	Disk& operator=(const Disk&);
	Disk& operator=(Disk&&);
	const Imenik* GetImenik() const;
	Imenik* GetImenik();
};

#endif 