#pragma once

namespace Engine{

//Getters
inline BlockAllocator::BlockDescriptor * BlockAllocator::unusedDescriptorsHeadGetter() const { return unusedDescriptorsHead; }
inline BlockAllocator::BlockDescriptor * BlockAllocator::freeDescriptorsHeadGetter() const { return freeDescriptorsHead; }
inline BlockAllocator::BlockDescriptor * BlockAllocator::outstandingDescriptorsHeadGetter() const { return outstandingDescriptorsHead; }

}