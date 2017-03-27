#ifndef COPYLOCK_HPP
#define COPYLOCK_HPP

/* =========================================================== *
 * SFGF (c) Kamil Koczurek | koczurekk@gmail.com               *
 * GNU GPL v3 License http://www.gnu.org/licenses/gpl-3.0.html *
 * =========================================================== */

namespace sfgf {
	//! \brief Non–copyable class
	//!
	//! Used as member in classes that are meant to be non–copyable, not a part of private API thus may be used in normal code.
	class CopyLock {
	private:
		void operator=(const CopyLock&) = delete;
		CopyLock(const CopyLock&) = delete;
		CopyLock(CopyLock&&) = delete;

	public:
		//! \brief Default–default constructor
		//!
		//! Does pretty much nothing
		CopyLock() = default;
	};
}

#endif // COPYLOCK_HPP
