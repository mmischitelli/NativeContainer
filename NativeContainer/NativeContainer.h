#pragma once

#include <map>
#include <memory>
#include <type_traits>
#include <functional>

#include "ILifetimeManager.h"
#include "ResolvableInterface.h"

class NativeContainer
{
	std::map<ClassUniqueId, std::shared_ptr<ILifetimeManager>> m_RegisteredInstances;

public:

	template<typename Interface, typename Type, template<typename> class LifetimeManager>
	void RegisterType()
	{
		static_assert((std::is_base_of<ILifetimeManager, LifetimeManager<Type>>::value), "The LifetimeManager class must derive from ILifetimeManager");
		static_assert((std::is_base_of<IResolvableType, Interface>::value), "The interface you are trying to register must derive from IResolvableType");
		static_assert((std::is_base_of<Interface, Type>::value), "The type you are trying to register must derive from the interface you provided as Interface");

		auto lifetimeManager = std::make_shared<LifetimeManager<Type> >();
		m_RegisteredInstances.insert(std::make_pair(Interface::GetStaticTypeId(), lifetimeManager));
	}

	template<typename Interface>
	[[nodiscard]] std::shared_ptr<Interface> Resolve() const
	{
		static_assert((std::is_base_of<IResolvableType, Interface>::value), "The interface you are trying to register must derive from IResolvableType");

		const auto kManager = m_RegisteredInstances.find(Interface::GetStaticTypeId());
		if (kManager == m_RegisteredInstances.end()) {
			return {};
		}

		auto object = kManager->second->template GetInstance<Interface>();

		return object;
	}
};
