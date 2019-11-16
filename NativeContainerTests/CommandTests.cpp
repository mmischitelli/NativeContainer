#define BOOST_TEST_MODULE Container
#include <boost/test/included/unit_test.hpp>
#include "../NativeContainer/NativeContainer.h"
#include "Counter.h"

BOOST_AUTO_TEST_CASE(container_controlled_instance)
{
	auto container = std::make_shared<NativeContainer>();
	container->RegisterType<CounterInterface, Counter, ContainerControlledManager>();

	{
		auto simpleTest = container->Resolve<CounterInterface>();
		simpleTest->Increment();
	}
	{
		auto simpleTest = container->Resolve<CounterInterface>();
		simpleTest->Increment();
	}
	{
		auto simpleTest = container->Resolve<CounterInterface>();
		BOOST_TEST(simpleTest->GetValue() == 2);
	}
}

BOOST_AUTO_TEST_CASE(container_per_resolve_instance)
{
	auto container = std::make_shared<NativeContainer>();
	container->RegisterType<CounterInterface, Counter, PerResolveManager>();

	{
		auto simpleTest = container->Resolve<CounterInterface>();
		simpleTest->Increment();
	}
	{
		auto simpleTest = container->Resolve<CounterInterface>();
		simpleTest->Increment();
	}
	{
		auto simpleTest = container->Resolve<CounterInterface>();
		BOOST_TEST(simpleTest->GetValue() == 0);
	}
}

BOOST_AUTO_TEST_CASE(container_externally_managed_instance_1)
{
	auto container = std::make_shared<NativeContainer>();
	container->RegisterType<CounterInterface, Counter, ExternallyControlledManager>();

	{
		auto simpleTest = container->Resolve<CounterInterface>();
		simpleTest->Increment();
	}
	{
		auto simpleTest = container->Resolve<CounterInterface>();
		simpleTest->Increment();
	}
	{
		auto simpleTest = container->Resolve<CounterInterface>();
		BOOST_TEST(simpleTest->GetValue() == 0);
	}
}

BOOST_AUTO_TEST_CASE(container_externally_managed_instance_2)
{
	auto container = std::make_shared<NativeContainer>();
	container->RegisterType<CounterInterface, Counter, ExternallyControlledManager>();

	auto storage = container->Resolve<CounterInterface>();
	storage->Increment();

	{
		auto simpleTest = container->Resolve<CounterInterface>();
		simpleTest->Increment();
	}
	{
		auto simpleTest = container->Resolve<CounterInterface>();
		simpleTest->Increment();
	}
	{
		auto simpleTest = container->Resolve<CounterInterface>();
		BOOST_TEST(simpleTest->GetValue() == 3);
	}
}
