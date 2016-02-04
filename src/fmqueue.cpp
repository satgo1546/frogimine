// Copyright 2016 Frog Chen
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=============================================================================
// ■ fmqueue.cpp
//-----------------------------------------------------------------------------
//   队列的模板类。使用的时候需要自行用数组分配内存，因为内核里没有new。
//=============================================================================

template <class T> class FMQueue {
	//-------------------------------------------------------------------------
	// ● 定义
	//-------------------------------------------------------------------------
private:
	T* array_start;
	T* array_end;
	T* front;
	T* rear;

	//-------------------------------------------------------------------------
	// ● 初始化对象
	//-------------------------------------------------------------------------
public:
	FMQueue(T* array, unsigned int size) {
		array_start = array;
		array_end = array + size - 1;
		front = array;
		rear = array;
	}

	//-------------------------------------------------------------------------
	// ● 修理超越界限的指针
	//-------------------------------------------------------------------------
private:
	void fix_ptrs() {
		if (front > array_end) front = array_start;
		if (rear > array_end) rear = array_start;
	}

	//-------------------------------------------------------------------------
	// ● 入队
	//-------------------------------------------------------------------------
public:
	void push(T data) {
		*rear = data;
		rear++;
		fix_ptrs();
	}

	//-------------------------------------------------------------------------
	// ● 出队
	//-------------------------------------------------------------------------
public:
	T shift() {
		T r = *front;
		front++;
		fix_ptrs();
		return r;
	}

	//-------------------------------------------------------------------------
	// ● 判定是否为空
	//-------------------------------------------------------------------------
public:
	bool is_empty() {
		return front == rear;
	}
};
