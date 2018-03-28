
// "InstanceOf"
//https://stackoverflow.com/questions/500493/c-equivalent-of-instanceof
// usage: if (instanceof<BaseClass>(ptr)) { ... }
template<typename Base, typename T>
inline bool instanceof(const T*) { return std::is_base_of<Base, T>::value; }

// Other tools have their place here
