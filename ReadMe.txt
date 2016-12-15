The BitArray Class:

Header file is located in the Engine project folder named BitArray.h
.Cpp file is located in the Engine project folder named BitArray.cpp

In the .cpp I implemented the functionality for handling bits.

In the MonsterChase.cpp file I ran Joe's BitArray unit test. To test it, uncomment it.

The FixedBlockAllocator Class:

Header file is located in the Engine project folder named FixedBlockAllocator.h
.Cpp file is located in the Engine project folder named FixedBlockAllocator.cpp

I added the _alloc functions and _free functions to handle allocations and freeing blocks
form the FixedSizeBlockAllocators I created.

The FSAManager Class:

Header file is located in the Engine project folder named FSAManager.h
.Cpp file is located in the Engine project folder named FSAManager.cpp

In this class I manage the construction of my 4 FSAs with placement new to allocate memory
for them and their BitArray from the BlockAllocator created in MonsterChase.cpp.

The NewDelete Class:

Header file is located in the Engine project folder named NewDelete.h
.Cpp file is located in the Engine project folder named NewDelete.cpp

In this class I created functions for finding my FSAs to verify if they match the size requirement the 
user wants when calling new. To allocate memory for them beforehand, I implemented a placement new function
that takes a BlockAllocator  pointer.

The FSA_UnitTest:

.Cpp file is located in the MonsterChase project folder named FSA_UnitTest.cpp

In this unit test I use one of my FSA's (the one with block sizes of 16 bytes and a number of blocks equal to 20)
to test _alloc, _free,AreAllSet() and  IsBitSet().

Thanks Joe!

