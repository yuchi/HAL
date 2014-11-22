/**
 * JavaScriptCoreCPP
 * Author: Matthew D. Langston
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _JAVASCRIPTCORECPP_JSOBJECT_HPP_
#define _JAVASCRIPTCORECPP_JSOBJECT_HPP_

#include "JavaScriptCoreCPP/detail/JSBase.hpp"
#include "JavaScriptCoreCPP/JSContext.hpp"
#include "JavaScriptCoreCPP/JSPropertyAttribute.hpp"
#include "JavaScriptCoreCPP/JSPropertyNameArray.hpp"

#include <memory>
#include <vector>
#include <unordered_set>

namespace JavaScriptCoreCPP {
  class JSString;
  class JSValue;
  class JSClass;
  class JSPropertyNameAccumulator;
  class JSPropertyNameArray;
  
  class JSExportObject;
  
  namespace detail {
    template<typename T>
    class JSExportClass;
  }
}

namespace JavaScriptCoreCPP {
  
  /*!
   @class
   
   @discussion A JSObject is an RAII wrapper around a JSObjectRef, the
   JavaScriptCore C API representation of a JavaScript object. This is
   the base class for all JavaScript objects JSObject:
   
   JSFunction
   JSArray
   JSDate
   JSError
   JSRegExp
   
   The only way to create a JSObject is by using the
   JSContext::CreateObject member functions.
   */
  class JAVASCRIPTCORECPP_EXPORT JSObject JAVASCRIPTCORECPP_PERFORMANCE_COUNTER1(JSObject) {
    
  public:
    
    /*!
     @method
     
     @abstract Determine whether this JavaScript object has a
     property.
     
     @param property_name The name of the property to set.
     
     @result true if this JavaScript object has the property.
     */
    virtual bool HasProperty(const JSString& property_name) const JAVASCRIPTCORECPP_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Return a property of this JavaScript object.
     
     @param property_name The name of the property to get.
     
     @result The property's value if this JavaScript object has the
     property, otherwise JSUndefined.
     
     @throws std::runtime_error if getting the property threw a
     JavaScript exception.
     */
    virtual JSValue GetProperty(const JSString& property_name) const final;
    
    /*!
     @method
     
     @abstract Return a property of this JavaScript object by numeric
     index. This method is equivalent to calling GetProperty with a
     string containing the numeric index, but provides optimized
     access for numeric properties.
     
     @param property_index An integer value that is the property's
     name.
     
     @result The property's value if this JavaScript object has the
     property, otherwise JSUndefined.
     
     @throws std::runtime_error if getting the property threw a
     JavaScript exception.
     */
    virtual JSValue GetProperty(unsigned property_index) const final;
    
    /*!
     @method
     
     @abstract Set a property on this JavaScript object with an
     optional set of attributes.
     
     @param property_name The name of the property to set.
     
     @param value The value of the the property to set.
     
     @param attributes An optional set of property attributes to give
     to the property.
     
     @result true if the the property was set.
     
     @throws std::runtime_error if setting the property threw a
     JavaScript exception.
     */
    virtual void SetProperty(const JSString& property_name, const JSValue& property_value, const std::unordered_set<JSPropertyAttribute>& attributes = {}) final;
    
    /*!
     @method
     
     @abstract Set a property on this JavaScript object by numeric
     index. This method is equivalent to calling SetProperty with a
     string containing the numeric index, but provides optimized
     access for numeric properties.
     
     @param property_index An integer value that is the property's
     name.
     
     @param value The value of the the property to set.
     
     @throws std::runtime_error if setting the property threw a
     JavaScript exception.
     */
    virtual void SetProperty(unsigned property_index, const JSValue& property_value) final;
    
    /*!
     @method
     
     @abstract Delete a property from this JavaScript object.
     
     @param property_name The name of the property to delete.
     
     @result true if the property was deleted.
     
     @throws std::runtime_error if deleting the property threw a
     JavaScript exception.
     */
    virtual bool DeleteProperty(const JSString& property_name) final;
    
    /*!
     @method
     
     @abstract Return the names of this JavaScript object's enumerable
     properties.
     
     @result A JSPropertyNameArray containing the names object's
     enumerable properties.
     */
    virtual JSPropertyNameArray GetPropertyNames() const JAVASCRIPTCORECPP_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Determine whether this object can be called as a
     function.
     
     @result true if this object can be called as a function.
     */
    virtual bool IsFunction() const JAVASCRIPTCORECPP_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Call this JavaScript object as a function. A
     std::runtime_error exception is thrown if this JavaScript object
     can't be called as a function.
     
     @discussion In the JavaScript expression 'myObject.myFunction()',
     the 'this_object' parameter will be set to 'myObject' and this
     JavaScript object is 'myFunction'.
     
     @param arguments Optional JSValue argument(s) to pass to the
     function.
     
     @param this_object An optional JavaScript object to use as
     'this'. The default value is this JavaScript object.
     
     @result Return the function's return value.
     
     @throws std::runtime_error if either this JavaScript object can't
     be called as a function, or calling the function itself threw a
     JavaScript exception.
     */
    
    virtual JSValue operator()(                                                            ) final;
    virtual JSValue operator()(JSValue&                     argument                       ) final;
    virtual JSValue operator()(const JSString&              argument                       ) final;
    virtual JSValue operator()(const std::vector<JSValue>&  arguments                      ) final;
    virtual JSValue operator()(const std::vector<JSString>& arguments                      ) final;
    
    virtual JSValue operator()(                                        JSObject this_object) final;
    virtual JSValue operator()(JSValue&                     argument , JSObject this_object) final;
    virtual JSValue operator()(const JSString&              argument , JSObject this_object) final;
    virtual JSValue operator()(const std::vector<JSValue>&  arguments, JSObject this_object) final;
    virtual JSValue operator()(const std::vector<JSString>& arguments, JSObject this_object) final;
    
    /*!
     @method
     
     @abstract Determine whether this object can be called as a
     constructor.
     
     @result true if this object can be called as a constructor.
     */
    virtual bool IsConstructor() const JAVASCRIPTCORECPP_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Call this JavaScript object as a constructor as if in a
     'new' expression.
     
     @param arguments Optional JSValue argument(s) to pass to the
     constructor.
     
     @result The JavaScript object of the constructor's return value.
     
     @throws std::runtime_error if either this JavaScript object can't
     be called as a constructor, or calling the constructor itself
     threw a JavaScript exception.
     */
    virtual JSObject CallAsConstructor(                                      ) final;
    virtual JSObject CallAsConstructor(const JSValue&               argument ) final;
    virtual JSObject CallAsConstructor(const JSString&              argument ) final;
    virtual JSObject CallAsConstructor(const std::vector<JSString>& arguments) final;
    virtual JSObject CallAsConstructor(const std::vector<JSValue>&  arguments) final;
    
    /*!
     @method
     
     @abstract Return this JavaScript object's prototype.
     
     @result This JavaScript object's prototype.
     */
    virtual JSValue GetPrototype() const JAVASCRIPTCORECPP_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Sets this JavaScript object's prototype.
     
     @param value The value to set as this JavaScript object's
     prototype.
     */
    virtual void SetPrototype(const JSValue& js_value) JAVASCRIPTCORECPP_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Return the execution context of this JavaScript value.
     
     @result The the execution context of this JavaScript value.
     */
    virtual JSContext get_context() const JAVASCRIPTCORECPP_NOEXCEPT final {
      return js_context__;
    }
    
    /*!
     @method
     
     @abstract Convert this JSObject to a JSValue.
     
     @result A JSValue with the result of conversion.
     */
    virtual operator JSValue() const final;
    
    /*!
     @method
     
     @abstract Return a std::shared_ptr<T> to this object's private
     data.
     
     @result A std::shared_ptr<T> to this object's private data if the
     object has private data of type T*, otherwise nullptr.
     */
    template<typename T>
    std::shared_ptr<T> GetPrivate() const JAVASCRIPTCORECPP_NOEXCEPT;
    
    
    virtual ~JSObject()                  JAVASCRIPTCORECPP_NOEXCEPT;
    JSObject(const JSObject&)            JAVASCRIPTCORECPP_NOEXCEPT;
    JSObject(JSObject&&)                 JAVASCRIPTCORECPP_NOEXCEPT;
    JSObject& operator=(const JSObject&);
    JSObject& operator=(JSObject&&);
    void swap(JSObject&)                 JAVASCRIPTCORECPP_NOEXCEPT;
    
  protected:
    
    // Only JSContext uses the following constructor.
    friend class JSContext;
    
    JSObject(const JSContext& js_context, const JSClass& js_class, void* private_data = nullptr);
    
    // In addition to derived classes, these classes need access to
    // the following JSObject constructor.
    
    friend class JSValue;
    
    // For GetPrivate, and SetPrivate and the static functions.
    template<typename T>
    friend class detail::JSExportClass;
    
    // For interoperability with the JavaScriptCore C API.
    JSObject(const JSContext& js_context, JSObjectRef js_object_ref);
    
    // These classes need access to operator JSObjectRef().
    friend class JSPropertyNameArray;
    
    // For interoperability with the JavaScriptCore C API.
    virtual operator JSObjectRef() const JAVASCRIPTCORECPP_NOEXCEPT final {
      return js_object_ref__;
    }
    
  private:
    
    /*!
     @method
     
     @abstract Call this JavaScript object as a function.
     
     @discussion In the JavaScript expression 'myObject.myFunction()',
     the 'this_object' parameter will be set to 'myObject' and this
     JavaScript object is 'myFunction'.
     
     @param arguments Optional JSValue argument(s) to pass to the
     function.
     
     @param this_object The JavaScript object to use as 'this'.
     
     @result Return the function's return value.
     
     @throws std::runtime_error if either this JavaScript object can't
     be called as a function, or calling the function itself threw a
     JavaScript exception.
     */
    virtual JSValue CallAsFunction(const std::vector<JSValue>&  arguments, JSObject this_object);

    /*!
     @method
     
     @abstract Gets this object's private data.
     
     @result A void* that is this object's private data, if the object
     has private data, otherwise nullptr.
     */
  public:
    // FIXME: This should be private.
    virtual void* GetPrivate() const JAVASCRIPTCORECPP_NOEXCEPT final;
  private:
    
    /*!
     @method
     
     @abstract Set this object's private data. Note that you must use
     the JSObject constructor taking a custom JSClass in order to use
     this method because the default JSObject constructor does not
     allocate storage for private data.
     
     @param data A void* to set as this object's private data.
     
     @result true if this object can store private data.
     */
    virtual bool SetPrivate(void* data) const JAVASCRIPTCORECPP_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract Collect the names of this JavaScript object's
     properties.
     
     @discussion Derived classes should provide only the names of
     properties that this JavaScript object provides through the
     GetProperty and SetProperty methods. Other property names are
     automatically added from properties vended by the JavaScript
     object's parent class chain and properties belonging to the
     JavaScript object's prototype chain.
     
     @param accumulator A JavaScript property name accumulator in
     which to accumulate the names of this JavaScript object's
     properties. Use JSPropertyNameAccumulator::AddName to add
     property names to the accumulator. Property name accumulators are
     used by JavaScript for...in loops.
     */
    virtual void GetPropertyNames(const JSPropertyNameAccumulator& accumulator) const JAVASCRIPTCORECPP_NOEXCEPT final;
    
    JSContext   js_context__;

    // Silence 4251 on Windows since private member variables do not
    // need to be exxported from a DLL.
#pragma warning(push)
#pragma warning(disable: 4251)
    JSObjectRef js_object_ref__;
#pragma warning(pop)
    
#undef  JAVASCRIPTCORECPP_JSOBJECT_LOCK_GUARD
#ifdef  JAVASCRIPTCORECPP_THREAD_SAFE
    std::recursive_mutex mutex__;
#define JAVASCRIPTCORECPP_JSOBJECT_LOCK_GUARD std::lock_guard<std::recursive_mutex> lock(mutex__)
#else
#define JAVASCRIPTCORECPP_JSOBJECT_LOCK_GUARD
#endif  // JAVASCRIPTCORECPP_THREAD_SAFE
  };
  
  inline
  void swap(JSObject& first, JSObject& second) JAVASCRIPTCORECPP_NOEXCEPT {
    first.swap(second);
  }
  
  template<typename T>
  std::shared_ptr<T> JSObject::GetPrivate() const JAVASCRIPTCORECPP_NOEXCEPT {
    return std::shared_ptr<T>(std::make_shared<JSObject>(*this), dynamic_cast<T*>(reinterpret_cast<JSExportObject*>(GetPrivate())));
  }
  
} // namespace JavaScriptCoreCPP {

#endif // _JAVASCRIPTCORECPP_JSOBJECT_HPP_
