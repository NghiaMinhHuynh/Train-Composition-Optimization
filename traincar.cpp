// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include "traincar.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//
//Implement for PushBack function
void PushBack(TrainCar*& head, TrainCar* makeCar) {
    if (head == NULL) {
        head = makeCar;
        head->next = NULL;
        head->prev = NULL;
    }
    else {
        TrainCar* temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = makeCar;
        makeCar->prev = temp;
        makeCar->next = NULL;
    }
}
//Implement for Delete all cars function
void DeleteAllCars(TrainCar*& head) {
    TrainCar* store;
    while (head != NULL) {
        store = head->next;
        
        delete head;
        head = store;
    }
}
void PushFront(TrainCar*& head, TrainCar* makeCar) {
    makeCar->next = NULL;
    makeCar->prev = NULL;
    if (head == NULL) {
        head = makeCar;
    }
    else {
        head->prev = makeCar;
        makeCar->next = head;
        head = makeCar;
    }
}

//Implement for Separate function
void Separate(TrainCar*& original, TrainCar*& train2, TrainCar*& train3) {
    // Total car
    int count_car = 0;
    TrainCar* temp = original;
    while (temp != NULL) {
        count_car++;
        temp = temp->next;
       
    }
    int count_train2 = count_car / 2;

    int i_car = 0;
    int i_eng = 0;
    temp = original;
    train2 = original;
    //train2
    while (i_car < count_train2)
    {
        i_car++;
        if (temp->isEngine()) {
            i_eng++;
        }
     
        temp = temp->next;
    }
    temp = temp->prev;
    train3 = temp->next;
    temp->next = NULL;
    train3->prev = NULL;
    original = NULL;
    
    if (i_eng == 0) 
    {
        TrainCar* temp2 = train2;
        TrainCar* temp3 = train3;
        bool is_head_train2 = false;
        bool is_head_train3 = false;
        if (!train2->isEngine())
        {
            is_head_train2 = true;
        }
        if (train3->isEngine())
        {
            is_head_train3 = true;
        }
        // find postion of engine in train2
        while (temp2 != NULL)
        {
            if (!temp2->isEngine())
            {
                break;
            }
            temp2 = temp2->next;
        }
        // find postsion of not engine in train3
        while (temp3 != NULL)
        {
            if (temp3->isEngine())
            {
                break;
            }
            temp3 = temp3->next;
        }
        TrainCar* temp2_next = temp2->next;
        TrainCar* temp2_prev = temp2->prev;
        TrainCar* temp3_next = temp3->next;
        TrainCar* temp3_prev = temp3->prev;
        temp2->next = temp3->next;
        temp2->prev = temp3->prev;
        temp3->next = temp2_next;
        temp3->prev = temp2_prev;
        temp2_next->prev = temp3;
        temp3_next->prev = temp2;

        if (temp2_prev != NULL)
        {
            temp2_prev->next = temp3;
        }
        if (temp3_prev != NULL)
        {
            temp3_prev->next = temp2;
        }

        if (is_head_train2)
        {
            train2 = temp3;
        }
        if (is_head_train3)
        {
            train3 = temp2;
        }
    }

    if (i_eng == 2) // if train2 have 2 engine
    {
        TrainCar* temp2 = train2;
        TrainCar* temp3 = train3;
        bool is_head_train2 = false;
        bool is_head_train3 = false;
        if (train2->isEngine())
        {
            is_head_train2 = true;
        }
        if (!train3->isEngine())
        {
            is_head_train3 = true;
        }
        // find postion of engine in train2
        while (temp2 != NULL)
        {
            if (temp2->isEngine())
            {
                break;
            }
            temp2 = temp2->next;
        }
        // find postsion of not engine in train3
        while (temp3 != NULL)
        {
            if (!temp3->isEngine())
            {
                break;
            }
            temp3 = temp3->next;
        }
        TrainCar* temp2_next = temp2->next;
        TrainCar* temp2_prev = temp2->prev;
        TrainCar* temp3_next = temp3->next;
        TrainCar* temp3_prev = temp3->prev;
        temp2->next = temp3->next;
        temp2->prev = temp3->prev;
        temp3->next = temp2_next;
        temp3->prev = temp2_prev;
        temp2_next->prev = temp3;
        temp3_next->prev = temp2;

        if (temp2_prev != NULL)
        {
            temp2_prev->next = temp3;
        }
        if (temp3_prev != NULL)
        {
            temp3_prev->next = temp2;
        }
        
        if (is_head_train2)
        {
            train2 = temp3;
        }
        if (is_head_train3)
        {
            train3 = temp2;
        }
    }

}
//Implement for ShipFreight function
std::vector<TrainCar*> ShipFreight(TrainCar*& all_engines, TrainCar*& all_freight, int min_speed, int max_cars) {
    
    std::vector<TrainCar*> v;
    
    
    while (all_engines != NULL && all_freight != NULL) {
        int count_car = 0;
        TrainCar* head;
        head = NULL;
        TrainCar* temp = all_engines->next;
        PushBack(head, all_engines);
        all_engines = temp;
        if (temp != NULL)
        {
            all_engines->prev = NULL;
            count_car++;
        }
        while (all_freight != NULL) {
            if (count_car < max_cars) {
                temp = all_freight->next;
                PushBack(head, all_freight);
                all_freight = temp;
                if (temp != NULL)
                {
                    all_freight->prev = NULL;
                }
                count_car++;
            }
            else {
                break;
            }
            if (CalculateSpeed(head) < min_speed && count_car < max_cars && all_engines != NULL)
            {
                while (CalculateSpeed(head) < min_speed && count_car < max_cars && all_engines != NULL)
                {
                    temp = all_engines->next;
                    head->prev = all_engines;
                    all_engines->next = head;
                    all_engines->prev = NULL;
                    head = all_engines;
                    count_car++;
                    all_engines = temp;
                    if (temp != NULL)
                    {
                        all_engines->prev = NULL;
                    }
                }
            }
            
            else if (CalculateSpeed(head) < min_speed)
            {
                temp = head;
               
                while (temp->next->next != NULL)
                {
                    temp = temp->next;
                }
                // remote tail
                TrainCar* tail = temp;
                TrainCar* Pretail = temp->next;
                tail->next = NULL;
                
                if (all_freight != NULL)
                {
                    all_freight->prev = Pretail;
                    Pretail->next = all_freight;
                    Pretail->prev = NULL;
                    all_freight = Pretail;
                }
                else
                {
                    all_freight = Pretail;
                    all_freight->next = NULL;
                    all_freight->prev = NULL;
                }
            }
        }
        if (count_car)
        {
            v.push_back(head);
        }
    }
    return v;
}
//Implement for TotalWeightAndCountCars function
void TotalWeightAndCountCars(TrainCar* head, int& total_weight, int& num_engines, int& num_freight_cars, int& num_passenger_cars, int& num_dining_cars, int& num_sleeping_cars) {
    total_weight = 0;
    num_engines = 0;
    num_freight_cars = 0;
    num_passenger_cars = 0;
    num_dining_cars = 0;
    num_sleeping_cars = 0;
    while (head != NULL) {
        total_weight = total_weight + head->getWeight();
        if (head->isEngine()) {
            num_engines++;
        }
        if (head->isFreightCar()) {
            num_freight_cars++;
        }
        if (head->isPassengerCar()) {
            num_passenger_cars++;
        }
        if (head->isDiningCar()) {
            num_dining_cars++;
        }
        if (head->isSleepingCar()) {
            num_sleeping_cars++;
        }
        head = head->next;
    }
}
//Implement for CalculateSpeed function
float CalculateSpeed(TrainCar* head) {
    int total_weight = 0;
    int num_engines = 0;
    //find num engines and total weight
    while (head != NULL) {
        total_weight = total_weight + head->getWeight();
        if (head->isEngine()) {
            num_engines++;
        }
        head = head->next;
    }
    float speed;
    long long int num = 3000;
    speed = (num_engines * num * 550 * 3600) / float(20 * 2 * 5280 * total_weight);
    return speed;
}
//Implement for AverageDistanceToDiningCar function
float AverageDistanceToDiningCar(TrainCar* train) {
    TrainCar* dtemp1;
    int countd1 = 0;
    TrainCar* dtemp2;
    int countd2 = 0;
    int dist = 0;
    float avg = 0;
    int count_car = 0;
    while (train != NULL)
    {
        //look for the closest dining car
        if (train->isPassengerCar())
        {
            dtemp1 = train;
            dtemp2 = train;
            while (dtemp1 != NULL && !dtemp1->isDiningCar())
            {
                dtemp1 = dtemp1->next;
                if (dtemp1 != NULL && dtemp1->isEngine())
                {
                    countd1 = -1;
                    break;
                }
                if (dtemp1 == NULL)
                {
                    break;
                }
                countd1++;
            }
            while (dtemp2 != NULL && !dtemp2->isDiningCar()){
                dtemp2 = dtemp2->prev;
                if (dtemp2 != NULL && dtemp2->isEngine()){
                    countd2 = -1;
                    break;
                }
                if (dtemp2 == NULL){
                    break;
                }
                countd2++;
            }
            if (countd1 < countd2 && countd1 != -1 && countd1 != 0) {
                dist += countd1;
            }
                
            if (countd1 > countd2 && (countd2 == -1 || countd2 == 0) && countd1 != 0) {
                dist += countd1;
            }
                
            if (countd2 < countd1 && countd2 != -1 && countd2 != 0) {
                dist += countd2;
            }
                
            if (countd2 > countd1 && (countd1 == -1 || countd1 == 0) && countd2 != 0) {
                dist += countd2;
            }
               
            if (countd2 == countd1 && countd2 != -1 && countd2 != 0) {
                dist += countd2;
            }
                
            if ((countd1 == -1 && countd2 == -1) || (countd1 == 0 && countd1 == -1) || (countd1 == -1 && countd2 == 0)){
                dist = -1;
                break;
            }
            count_car++;  
            countd1 = 0;
            countd2 = 0;
        }
        train = train->next;
    }
    if (dist == -1) {
        return dist;
    }
    else
    {
        avg = ((float)dist) / count_car;
        return avg;
    }
}
//Implement for ClosestEngineToSleeperCar function
float ClosestEngineToSleeperCar(TrainCar* train) {
    TrainCar* stemp1;
    TrainCar* stemp2;
    int count1 = 0;
    int count2 = 0;
    int dist = 0;
    int dtemp = 0;
    while (train != NULL) {
        //look for the sleeping car
        if (train->isSleepingCar())
        {
            stemp1 = train;
            stemp2 = train;
            while (stemp1 != NULL && !stemp1->isEngine())
            {
                stemp1 = stemp1->next;
                if (stemp1 != NULL)
                {
                    count1++;
                    if (stemp1->isEngine()) {
                        break;
                    }
                }
                else
                {
                    count1 = -1;
                    break;
                }
            }
            while (stemp2 != NULL && !stemp2->isEngine())
            {
                stemp2 = stemp2->prev;
                if (stemp2 != NULL)
                {
                    count2++;
                    if (stemp2->isEngine())
                        break;
                }
                else
                {
                    count2 = -1;
                    break;
                }
            }
            if (count1 <= count2 && count1 != -1) {
                dist = count1;
            }
              
            if (count1 > count2 && count2 == -1) {
                dist = count1;
            }
                
            if (count2 < count1 && count2 != -1) {
                dist = count2;
            }
                
            if (count2 > count1 && count1 == -1) {
                dist = count2;
            }
            
            
            count1 = 0;
            count2 = 0;
            if (dtemp == 0) {
                dtemp = dist;
            }
            if (dist > dtemp)
            {
                dist = dtemp;
            }else
                dtemp = dist;
            }
        train = train->next;
    }
    return dist;
}

