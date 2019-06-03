#include <string.h>

class QuicksortRequest{
public:
	QuicksortRequest(std::string variation, std::string arr_type){
		this->variation = variation;
		this->arr_type = arr_type;
	}

	static QuicksortRequest build(std::string variation, std::string arr_type){
		return QuicksortRequest(variation, arr_type);
	}

	std::string get_variation(){
		return this->variation;
	}

	std::string get_arr_type(){
		return this->arr_type;
	}

	~QuicksortRequest(){}
private:
	std::string variation;
	std::string arr_type;
};