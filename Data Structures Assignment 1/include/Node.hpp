
#ifndef NODE_HPP
#define NODE_HPP


class Node {

public:

	Node();
	~Node();

	Node(int data);
	Node(Node* addr);// Yonetici listesindeki, satir adresini tutan alan
	Node(Node* addr, double avg);
	
	double avg;
	int data;
	Node* prev ;
	Node* next ;
	Node* addr ;
private:

};



#endif //NODE_HPP