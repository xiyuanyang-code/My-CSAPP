#ifndef MATH_TOOL_H
#define MATH_TOOL_H

#include <stdio.h>

#define PRICE_PER_SQUARE_CM 0.05
#define CALORIES_PER_SQUARE_CM 2.5

typedef struct {
  double cheese;
  double pepperoni;
  double mushroom;
  double olive;
  double basil;
} ToppingPrices;

typedef struct {
  double area;
  double price;
  double calories;
  double price_per_square_cm;
} PizzaInfo;

double calculate_circle_area(double radius);

double calculate_square_area(double radius);

double calculate_circle_circumference(double radius);

double calculate_square_perimeter(double side);

double inches_to_cm(double inches);

double cm_to_inches(double cm);

double calculate_base_price(double area, double price_per_square_cm);

double calculate_price_with_toppings(double base_price, int cheese_count,
                                     int pepperoni_count, int mushroom_count);

double calculate_total_calories(double area, double calories_per_square_cm);

double calculate_price_per_square_cm(double price, double area);

void print_pizza_info(PizzaInfo info);

PizzaInfo create_pizza_info(double radius, const char *type);

double calculate_discount(double price, double discount_percentage);

int recommend_pizza_size(int people_count);

double compare_value_for_money(double area1, double price1, double area2,
                               double price2);

#endif
