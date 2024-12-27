/** 
* @file YoneticiList.cpp
* @description List sinifindan kalitim almis Yonetici Listesi sinifidir. Yonetici listesine ait metodlari(ortalamaya gore ekle, ortalama bul, liste sil vb.) barindirir.
* @course 2.Ogretim A Grubu
* @assignment Odev_1
* @date 24/11/2022
* @author Burak Gun, burak.gun1@ogr.sakarya.edu.tr
*/



#include "YoneticiList.hpp"
#include "List.hpp"
#include "Node.hpp"
#include <iostream>

using namespace std;

YoneticiList::YoneticiList() 
{
	head = new Node;
	length = 0;
}

YoneticiList::~YoneticiList()
{
	;
}


// Addr:Satir head adresini tutar
// Average: Satir ortalamasý

void YoneticiList::AddByAvg(List* list, double avg)
{
	
	Node* iter = head;
	Node* node = new Node(list->getAddr() , avg);


	// dizi bos, yeni node olustur
	if (head->next == 0)
	{
		iter->next = node;
		node->prev = iter;
		node->next = 0;
	}
	else
	{
		// eðer ilk elemandan küçük ise, ilk sýraya ekle
		Node* iter = head;
		if (avg < head->next->avg)
		{
			Node* tmp = head->next;

			head->next = node;
			node->next = tmp;
			node->prev = head;
			tmp->prev = node;


		}
		else
		{
			Node* iter = head;

			// kendinden küçük olan elemanlarý atla. 
			// son elemana gelip gelmediðini kontrol et
			while (avg >= iter->avg && iter->next != 0)
			{
				iter = iter->next;
			}

			// üstteki fonksiyonun devamý olarak eklendi
			// yeni bir düðüm oluþtur
			if (avg <= iter->avg)
			{
				Node* tmp = iter->prev;

				node->next = iter;
				node->prev = iter->prev;

				tmp->next = node;
				iter->prev = node;
			}

			// dizinin sonuna eleman ekler
			// eklenecek olan sayi, listedeki en büyük eleman 
			if (avg > iter->avg && iter->next == 0)
			{
				iter->next = node;
				node->next = 0;
				node->prev = iter;
			}
		}




	}

	length++;

}



void YoneticiList::PrintList(List* list)
{
	Node* addr = list->getAddr();
	Node* iter = addr;

	for (int i = 0; i < list->Size()+1; i++)// head dahil olmadan length hesapþan
	{
		cout << "length: " << list->Size() << " data : " << iter->data << endl;
		iter = iter->next;


	}
}



extern int iterCurrentIndex;

Node* YoneticiList::GoToSatir(YoneticiList* yonetici)
{
	Node* YoneticiIter = yonetici->getAddr();
	Node* Addr;

	for (int i = 0; i < iterCurrentIndex; i++)
	{
		YoneticiIter = YoneticiIter->next;
	}
	Addr = YoneticiIter->addr;

	return Addr;

}


bool YoneticiList::IsSatirEmpty(YoneticiList* yonetici)
{
	Node* satirAddr = yonetici->GoToSatir(yonetici);

	if (satirAddr->next == 0) return true;

	return false;
}

// Sadece satirda bulunan liste elemanlarýný siler
// Node adresi silinmez

void YoneticiList::RemoveSatir(YoneticiList* yonetici)
{
	Node* satirAddr = yonetici->GoToSatir(yonetici);

	//if( IsSatirEmpty(yonetici) ) throw "Satir is Empty";

	Node* iter = satirAddr;

	while (iter != 0)
	{
		Node* temp = iter;
	
		iter=iter->next;
	
		delete temp;
	}
	// delete iter;

	//length--;
}

void YoneticiList::RemoveYoneticiNodeAt()
{
	
	Node* iter = head;

	for (int i = 0; i < iterCurrentIndex; i++)
	{
		iter = iter->next;
	}

	// head
	if (iter->prev == head)
	{
		// dizideki tek eleman ise
		// oncesi head, sonrasý null
		if(iter->next == 0)
		{
		
			head->next = 0;

			delete iter;
			
		}
		else
		{
			Node* temp = iter->next;
			head->next = temp;
			temp->prev = head;

			delete iter;
			
		}


	}
	else if (iter->next == 0) 
	{
		

		Node* temp = iter->prev;
		temp->next = 0;

		delete iter;
		// Yonetici listesinden son elemaný sildigimiz icin 
		// ekranda gosteren indeks degeri azaltildi 
		iterCurrentIndex--;
		
	}
	else
	{
	

		Node* temp1 = iter->prev;
		Node* temp2 = iter->next;

		temp1->next = temp2;
		temp2->prev = temp1;

		
		delete iter;
		

	}
	
	this->length--;
	

}

void YoneticiList::RemoveSatirNodeAt(YoneticiList* yonetici, int index)
{
	Node* satirAddr = yonetici->GoToSatir(yonetici);

	int size = yonetici->SizeOfNode(yonetici) - 1;

	if (index <0 || index > size)throw "Index Out of Range";

	Node* SatirIter = satirAddr;
	for (int i = 0; i < index; i++)
	{
		SatirIter = SatirIter->next;
	}

	Node* iter;
	Node* temp;
	Node* toBeDeleted;

	// ilk durum olmasý þartý
	if (index == 1)
	{
		// ilk ve son eleman
		if (size == 1 )
		{
			iter = SatirIter->prev;
			toBeDeleted = SatirIter;

			iter->next = 0;
			delete toBeDeleted;
		}
		else // ilk eleman
		{
			iter = SatirIter->prev;
			temp = SatirIter->next;

			toBeDeleted = SatirIter;

			iter->next = temp;
			temp->prev = iter;

			delete toBeDeleted;
		}


	}
	else
	{
		//son dugum olmasý sarti
		if (index == size) // head dugumu de sayiliyor
		{
			iter = SatirIter->prev;
			iter->next = 0;

			delete SatirIter;
		}
		else
		{
			iter = SatirIter->prev;
			toBeDeleted = SatirIter;
			temp = SatirIter->next;


			iter->next = temp;
			temp->prev = iter;

			delete toBeDeleted;
		}
	}

}

//kopyalama iþlemi yap, while sizeofnode == 0 removeat(1) ile nodu sil

int YoneticiList::SizeOfNode(YoneticiList* yonetici)
{
	Node* satirAddr = yonetici->GoToSatir(yonetici);


	int size = 0;
	Node* iter = satirAddr;
	while (iter != 0) {
		size++;
		iter = iter->next;
	}
	return size;
}

extern int verilerSatirSayisi;
void YoneticiList::CopyAndAddList(YoneticiList* yonetici)
{
	// yeni liste olustur
	YoneticiList* list = new YoneticiList;

	Node* satirAddr = yonetici->GoToSatir(yonetici);

	// butun verileri liste icine kopyala
	while (satirAddr != 0)
	{
		list->Add(satirAddr->data);
		satirAddr = satirAddr->next;
	}
	// diger diziden gelen head dugumunu sil
	list->RemoveAt(1);

	// satir dugumlerini siler
	yonetici->RemoveSatir(yonetici);

	//ilgili satira ait yonetici dugumunu siler
	yonetici->RemoveYoneticiNodeAt();

	// yeni listeyi listeyi yoneticiye ekle
	yonetici->AddByAvg(list, list->GetAvgOfList());

}
void YoneticiList::RandomDelete(YoneticiList* yonetici, int rand)
{
	
	
	int size = yonetici->SizeOfNode(yonetici);
	int yoneticiSize = yonetici->Size();
	

	// sadece head var ise
	if (size == 2) 
	{
		yonetici->RemoveSatirNodeAt(yonetici, 1); // ilk/son elemaný sil
		yonetici->RemoveYoneticiNodeAt();
	}
	else
	{
		yonetici->RemoveSatirNodeAt(yonetici, rand);
		yonetici->CopyAndAddList(yonetici);
	}
	
}


