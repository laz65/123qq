//macros for function declarations
//pdll.h
//function declarations according to the number of parameters
#define FUNC_LOADED 1

#define DECLARE_FUNCTION1(retVal, FuncName, Param1) \
   typedef  retVal (CALLBACK* TYPE_##FuncName)(Param1); \
   TYPE_##FuncName m_##FuncName; \
   short m_is##FuncName;\
   retVal FuncName(Param1 p1) \
   { \
      if (m_dllHandle) \
      { \
         if (FUNC_LOADED != m_is##FuncName) \
         {\
            m_##FuncName = NULL; \
            m_##FuncName = (TYPE_##FuncName)GetProcAddress(m_dllHandle, #FuncName); \
            m_is##FuncName = FUNC_LOADED;\
         }\
         if (NULL != m_##FuncName) \
            return m_##FuncName(p1); \
         else \
            return (retVal)NULL; \
      } \
      else \
         return (retVal)NULL; \
   }
// Fedorov I.L.14.11.07
#define DECLARE_FUNCTION2(retVal, FuncName, Param1, Param2, Param3) \
   typedef  retVal (CALLBACK* TYPE_##FuncName)(Param1, Param2, Param3); \
   TYPE_##FuncName m_##FuncName; \
   short m_is##FuncName;\
   retVal FuncName(Param1 p1, Param2 p2, Param3 p3) \
   { \
      if (m_dllHandle) \
      { \
         if (FUNC_LOADED != m_is##FuncName) \
         {\
            m_##FuncName = NULL; \
            m_##FuncName = (TYPE_##FuncName)GetProcAddress(m_dllHandle, #FuncName); \
            m_is##FuncName = FUNC_LOADED;\
         }\
         if (NULL != m_##FuncName) \
            return m_##FuncName(p1,p2,p3); \
         else \
            return (retVal)NULL; \
      } \
      else \
         return (retVal)NULL; \
   }
//end

class PDLL
{
public:
	HMODULE m_dllHandle;
	PDLL() {m_dllHandle = NULL; }
	~PDLL() {if (m_dllHandle) FreeLibrary (m_dllHandle);}
	void LoadDll(const LPCTSTR name) {m_dllHandle = LoadLibrary(name);}
};


//declare constructors
// ClassName is the user class name
#define DECLARE_CLASS(ClassName) \
   public:   \
   ClassName (const LPCTSTR name){LoadDll(name);} \
   ClassName () {PDLL();}

//class PDLL;//: public void;
