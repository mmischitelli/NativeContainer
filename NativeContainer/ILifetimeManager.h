#pragma once

#include <memory>

class ILifetimeManager
{
	friend class NativeContainer;
	
	template<typename InterfaceType>
	[[nodiscard]] std::shared_ptr<InterfaceType> GetInstance() {
		return std::static_pointer_cast<InterfaceType>(_GetInstance());
	}

protected:
	[[nodiscard]] virtual std::shared_ptr<void> _GetInstance() = 0;

public:
	ILifetimeManager() = default;
	virtual ~ILifetimeManager() = default;

	// Begin: deleted copy and move constructors / operators
	ILifetimeManager(const ILifetimeManager&) = delete;
	ILifetimeManager(ILifetimeManager&&) = delete;
	void operator=(const ILifetimeManager&) = delete;
	void operator=(ILifetimeManager&&) = delete;
	// End
};

// Creates a new object of requested type every time you call Resolve
template<typename DerivedType>
class PerResolveManager final : public ILifetimeManager
{
	/**
	 * Returns an instance of the type specified. The returned object is created anew every time the method is called.
	 * @return The new instance every time this method is called
	 */
	[[nodiscard]] std::shared_ptr<void> _GetInstance() override {
		return std::shared_ptr<void>(new DerivedType());
	}
};

// Creates a singleton object first time you call Resolve and then returns the same object on subsequent Resolve calls
template<typename DerivedType>
class ContainerControlledManager final : public ILifetimeManager
{
	std::shared_ptr<DerivedType> m_Instance;

	/**
	 * Returns an instance of the type specified. The returned object is added to the root set and is deleted once this lifetime manager is destroyed.
	 * @return The same instance every time this method is called
	 */
	[[nodiscard]] std::shared_ptr<void> _GetInstance() override
	{
		if (m_Instance == nullptr) {
			m_Instance = std::make_shared<DerivedType>();
		}
		return std::static_pointer_cast<void>(m_Instance);
	}
};

// Creates a new object every time you call Resolve, unless you're keeping a reference to it, in which case it acts similarly to ContainerControlledManager.
// It basically just holds a weak_ptr to the object, creating new ones if it's expired.
template<typename DerivedType>
class ExternallyControlledManager final : public ILifetimeManager
{
	std::weak_ptr<void> m_Instance;

	/**
	 * Returns an instance of the type specified. The returned object is NOT added to the root set, leaving the lifetime management to the developer.
	 * @return The same instance every time this method is called
	 */
	[[nodiscard]] std::shared_ptr<void> _GetInstance() override
	{
		if (!m_Instance.expired()) {
			return m_Instance.lock();
		}
		std::shared_ptr<void> instance = std::shared_ptr<void>(new DerivedType());
		m_Instance = instance;
		return instance;
	}
};