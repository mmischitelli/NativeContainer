#pragma once

typedef const void* ClassUniqueId;

#define ResolvableMagic() \
public: \
	static constexpr char m_kTypeId = 0; \
	static constexpr ClassUniqueId GetStaticTypeId() { return static_cast<ClassUniqueId>(&m_kTypeId); } \
	template<typename T> static constexpr bool SameAs(T* p = nullptr) { return &m_kTypeId == &T::m_kTypeId; } \
	virtual ClassUniqueId GetTypeId() const override { return GetStaticTypeId(); } \
private:

class IResolvableType
{
	friend class NativeContainer;

public:
	IResolvableType() = default;
	virtual ~IResolvableType() = default;
	
	IResolvableType(const IResolvableType&) = delete;
	IResolvableType(IResolvableType&&)		= delete;
	void operator=(const IResolvableType&)	= delete;
	void operator=(IResolvableType&&)		= delete;

	[[nodiscard]] virtual ClassUniqueId GetTypeId() const = 0;
};
