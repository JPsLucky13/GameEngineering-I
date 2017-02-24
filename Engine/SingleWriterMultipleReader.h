#pragma once
#ifndef __SINGLE_WRITER_REDER_H
#define __SINGLE_WRITER_MULTIPLE_READER_H

#include <Windows.h>

namespace Engine
{

	class SingleWriterMultipleReader
	{

	public: 
		SingleWriterMultipleReader()
		{
			InitializeSRWLock(&m_RWLock);
		}

		void ReadLock()
		{
			AcquireSRWLockShared(&m_RWLock);
		}
		
		bool TryReadLock()
		{
			return TryAcquireSRWLockShared(&m_RWLock) == TRUE;
		}

		void ReleaseReadLock()
		{
			ReleaseSRWLockShared(&m_RWLock);
		}

		void WriteLock()
		{
			AcquireSRWLockExclusive(&m_RWLock);
		}

		bool TryWriteLock()
		{
			return TryAcquireSRWLockExclusive(&m_RWLock) == TRUE;
		
		}

		void ReleaseWriteLock()
		{
			ReleaseSRWLockShared(&m_RWLock);
		}

	private:
		SRWLOCK m_RWLock;

	};


}
#endif // __SINGEL_WRITER_MULTIPLE_READER_H