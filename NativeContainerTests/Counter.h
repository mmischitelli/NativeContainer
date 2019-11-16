#pragma once

#include "../NativeContainer/ResolvableInterface.h"

class CounterInterface : public IResolvableType
{
	ResolvableMagic()

public:
	void Increment() { _Increment_Impl(); }
	int GetValue() const { return _GetValue_Impl(); }

private:
	virtual void _Increment_Impl() = 0;
	virtual int _GetValue_Impl() const = 0;
};

class Counter : public CounterInterface
{
	int m_Value;
	
public:
	Counter() : m_Value(0) { }
	
private:
	void _Increment_Impl() override { ++m_Value; }
	int _GetValue_Impl() const override { return m_Value; }
};