const char* getCallerIndentifierName() {
  return nullptr;
}

int getCallerLineNumber() {
  return 0;
}

class Object {
public:
  __attribute__((annotate("cash::source_info"))) Object() {
    name_ = getCallerIndentifierName();
    line_ = getCallerLineNumber();
  }  

private:
  const char* name_;
  int line_;
};

struct X {
  Object a;
};

int main() {
  Object obj;
  X x;    
}