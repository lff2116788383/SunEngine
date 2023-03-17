#pragma once

//#include <stdexcept>
//#include <assert.h>
#include <mutex>

   /* template <typename T>
    class  Singleton {
    public:
        template<typename... Args>
		static T* Instance(Args&&... args){
			if (m_pInstance == nullptr)
				m_pInstance = new T(std::forward<Args>(args)...);

			return m_pInstance;
		}


		static T* GetInstance(){
			if (m_pInstance == nullptr) {
				std::cout << "m_pInstance == nullptr class name:" << typeid(T).name() << std::endl;
			}
			assert(m_pInstance != nullptr);
			return m_pInstance;
		}

		static void DestroyInstance() {
			if (m_pInstance != nullptr)
			{
				delete m_pInstance;
				m_pInstance = nullptr;
			}
		}

    public:
        static T* m_pInstance;
    };

	template<typename T>
	T* Singleton<T>::m_pInstance = nullptr;*/

	template <typename T>
	class Singleton
	{
	public:
		static std::shared_ptr<T> Instance()
		{
			static std::once_flag flag;
			std::call_once(flag, []() {
				m_instance.reset(new T);
				});
			return m_instance;
		}
	private:
		Singleton() = default;
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		static std::shared_ptr<T> m_instance;
	};
	template<typename T>
	std::shared_ptr<T> Singleton<T>::m_instance;

	
#define DECL_SINGLETON(T)\
private:\
explicit T() {}\
friend class Singleton<T>;\
public:\
	static std::shared_ptr<T> GetInstance()\
	{\
		return Singleton<T>::Instance();\
	}

