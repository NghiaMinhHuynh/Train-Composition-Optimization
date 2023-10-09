// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//                 This file is #include'd from traincar.h and main.cpp
//
// =======================================================================
//
// There are a number of additional functions used in main.cpp that
// you need to declare and implement.  Study main.cpp and the provided
// output to determine the arguments, return type, and overall
// behavior.
//
// Add all required additional function prototypes here
// (you may also add your own helper function prototypes here too)
//
// Implement these functions in "traincar.cpp"
//
#include <vector>
#include <iostream>

void PushBack(TrainCar*& head, TrainCar* makeCar);
void DeleteAllCars(TrainCar*& head);
std::vector<TrainCar*> ShipFreight(TrainCar*& all_engines, TrainCar*& all_freight, int min_speed, int max_cars);
void Separate(TrainCar*& original, TrainCar*& train2, TrainCar*& train3);
void TotalWeightAndCountCars(TrainCar* head, int& total_weight, int& num_engines, int& num_freight_cars, int& num_passenger_cars, int& num_dining_cars, int& num_sleeping_cars);
float CalculateSpeed(TrainCar* head);
float AverageDistanceToDiningCar(TrainCar* train);
float ClosestEngineToSleeperCar(TrainCar* train);

