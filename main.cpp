#include <iostream>
#include <iterator>
#include <map>
#include <limits>
#include <list>

template<typename K, typename V>
class interval_map {
	std::map<K, V> map_;

public:
	interval_map(V const& val) {
		map_.insert(map_.end(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	}

	void assign(K const& keyBegin, K const& keyEnd, V const& val) {
		if (!(keyBegin < keyEnd)) return;

		using mapitr_t = typename decltype(map_)::iterator;

		// End of the input range
		mapitr_t itEnd = map_.find(keyEnd);
		if (auto l = map_.lower_bound(keyEnd); itEnd != map_.end())
			itEnd->second = l->second;
		else
			itEnd = map_.insert(map_.end(), std::make_pair(keyEnd, (--l)->second));

		// Beginning of the input range
		auto itBegin = map_.insert_or_assign(keyBegin, val).first;

		// Cleanup the new range
		map_.erase(std::next(itBegin), itEnd);

		// Make canonical
		auto itRight = itEnd;
		auto itLeft = (itBegin != map_.begin() ? std::prev(itBegin) : itBegin);
		while (itRight != itLeft) {
			auto itNext = std::prev(itRight);
			if (itRight->second == itNext->second)
				map_.erase(itRight);
			itRight = itNext;
		}
	}

	V const& operator[](K const& key) const {
		return (--map_.upper_bound(key))->second;
	}

	void print() {
		for (auto&&[key, val] : map_)
			std::cout << "[" << key << ':' << val << "]";
		std::cout << '\n';
	}
};

int main() {
	interval_map<int, char> map{ 'a' };
	map.print(); // [-2147483648:a]

	map.assign(3, 5, 'b');
	map.print(); // [-2147483648:a][3:b][5:a]

	map.assign(2, 3, 'c');
	map.print(); // [-2147483648:a][2:c][3:b][5:a]

	map.assign(2, 3, 'd');
	map.print(); // [-2147483648:a][2:d][3:b][5:a]

	map.assign(2, 4, 'e');
	map.print(); // [-2147483648:a][2:e][4:b][5:a]

	map.assign(4, 18, 'f');
	map.print(); // [-2147483648:a][2:e][4:f][18:a]

	map.assign(2, 8, 'g');
	map.print(); // [-2147483648:a][2:g][8:f][18:a]

	map.assign(0, 10, 'a');
	map.print(); // [-2147483648:a][10:f][18:a]

	map.assign(0, 20, 'a');
	map.print(); // [-2147483648:a]

	map.assign(0, 30, 'a');
	map.print(); // [-2147483648:a]
}
