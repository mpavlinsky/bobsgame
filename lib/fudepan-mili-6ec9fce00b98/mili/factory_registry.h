/*
factory_registry: A simple way to registry derived classes without .h file
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Leandro Ramos, FuDePAN 2012
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt in the root directory or
    copy at http://www.boost.org/LICENSE_1_0.txt)

    MiLi IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

//WARNING FactoryRegistry should NOT be used within static libraries
#ifndef FACTORY_REGISTRY_H
#   error Internal header file, DO NOT include this.
#endif
#include<string>

template <class BaseClass_, class Key_, class ConstructorParameterType_>
struct FactoryTraits
{
    typedef BaseClass_ BaseClass;
    typedef Key_ Key;
    typedef ConstructorParameterType_ ConstructorParameterType;
};


template <class DerivedRegistry, class Traits>
class BaseFactoryRegistry
{
protected:
    typedef typename Traits::BaseClass BaseClass;
    typedef typename Traits::Key Key;
    typedef typename Traits::ConstructorParameterType ConstructorParameterType;

    unsigned int users;
    static DerivedRegistry* instance;
    Factory<Key, BaseClass, ConstructorParameterType> fc;

    BaseFactoryRegistry(): users(0) {}

    virtual ~BaseFactoryRegistry()
    {
        deregister_factory();
    }

    template <class DerivedClass>
    void _register_factory(const Key& k)
    {
        ++users;
        fc.template register_factory<DerivedClass>(k);
    }

    bool _deregister_factory()
    {
        --users;
        return (users == 0);
    }
    typename Factory<Key, BaseClass>::KeyIterator _getConstructibleObjectsKeys()
    {
        return fc.getConstructibleObjectsKeys();
    }
public:
    template<class DerivedClass>
    static void register_factory(const Key& k)
    {
        if (instance == NULL)
            instance = new DerivedRegistry();
        instance->template _register_factory<DerivedClass>(k);
    }
    static void deregister_factory()
    {
        if (instance->_deregister_factory())
        {
            delete instance;
            instance = NULL;
        }
    }

    static typename Factory<Key, BaseClass>::KeyIterator getConstructibleObjectsKeys()
    {
        return instance->_getConstructibleObjectsKeys();
    }

};

template<class DerivedRegistry, class Traits>
DerivedRegistry* BaseFactoryRegistry<DerivedRegistry, Traits>::instance = NULL;

template <class BaseClass, class Key = std::string, class ConstructorParameterType = void>
class FactoryRegistry : public BaseFactoryRegistry < FactoryRegistry <BaseClass, Key, ConstructorParameterType>,
    FactoryTraits   <BaseClass, Key, ConstructorParameterType> >
{
public:
    static BaseClass* new_class(const Key& k, ConstructorParameterType p)
    {
        return BaseFactoryRegistry<FactoryRegistry, FactoryTraits<BaseClass, Key, ConstructorParameterType> >::instance->_new_class(k, p);
    }
private:
    BaseClass* _new_class(const Key& k, ConstructorParameterType p)
    {
        return this->fc.new_class(k, p);
    }
};

template <class BaseClass, class Key>
class FactoryRegistry<BaseClass, Key, void> : public BaseFactoryRegistry <   FactoryRegistry <BaseClass, Key, void>,
    FactoryTraits   <BaseClass, Key, void> >
{
public:
    static BaseClass* new_class(const Key& k)
    {
        return BaseFactoryRegistry<FactoryRegistry, FactoryTraits<BaseClass, Key, void> >::instance->_new_class(k);
    }
private:
    BaseClass* _new_class(const Key& k)
    {
        return this->fc.new_class(k);
    }
};

template<class BaseClass, class DerivedClass, class Key, class ConstructorParameterType = void>
class Registerer
{
public:
    Registerer(const Key& k)
    {
        mili::FactoryRegistry<BaseClass, Key, ConstructorParameterType>::template register_factory<DerivedClass>(k);
    }
    ~Registerer()
    {
        mili::FactoryRegistry<BaseClass, Key, ConstructorParameterType>::deregister_factory();
    }
};

#define REGISTER_FACTORIZABLE_CLASS(BaseClassName, DerivedClassName, keytype, key)           \
    static mili::Registerer<BaseClassName,DerivedClassName,keytype>  r##BaseClassName##DerivedClassName(key)

#define REGISTER_FACTORIZABLE_CLASS_WITH_ARG(BaseClassName, DerivedClassName, keytype, key, ConstructorParameterTypeName)   \
    static mili::Registerer<BaseClassName,DerivedClassName,keytype, ConstructorParameterTypeName>  rr##BaseClassName##DerivedClassName(key)
