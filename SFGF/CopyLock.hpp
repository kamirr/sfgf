#ifndef COPYLOCK_HPP
#define COPYLOCK_HPP

/* =========================================================== *
 * SFGF (c) Kamil Koczurek | koczurekk@gmail.com               *
 * GNU GPL v3 License http://www.gnu.org/licenses/gpl-3.0.html *
 * =========================================================== */

namespace sfgf {
	class CopyLock {
	private:
		void operator=(const CopyLock&) = delete;
		CopyLock(const CopyLock&) = delete;
		CopyLock(CopyLock&&) = delete;

	public:
		CopyLock() = default;
	};
}

#endif // COPYLOCK_HPP
