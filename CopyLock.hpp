#ifndef COPYLOCK_HPP
#define COPYLOCK_HPP

class CopyLock {
private:
	void operator=(const CopyLock&) = delete;
	CopyLock(const CopyLock&) = delete;
	CopyLock(CopyLock&&) = delete;

public:
	CopyLock() = default;
};

#endif // COPYLOCK_HPP