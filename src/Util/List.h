#ifndef GAMELIST_H
#define GAMELIST_H

#include <vector>
#include <assert.h>
#include <algorithm>

namespace SFMLGame{
	typedef unsigned int uint;

	template<class T>
	class List{
	private:
		std::vector<T> _data;

	public:
		List() :_data(0){}

		void Remove(T & item){
			_data.erase(std::remove(_data.begin(), _data.end(), item), _data.end() );
		}

		bool Contains(T & item){
			for(int i = 0; i < _data.size(); i++){
				if(_data[i] == item)
					return true;
			}
			return false;
		}

		void Add(T & item){
			_data.push_back(item);
		}

		T& operator[](const int index){
			return _data[index];
		}

		int size(){return _data.size(); }

		void clear(){
			_data.clear();
		}
	};


};

#endif