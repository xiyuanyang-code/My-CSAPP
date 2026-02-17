#include "math_tool.h"
#include <math.h>
#include <string.h>

double calculate_circle_area(double radius) { return M_PI * pow(radius, 2); }

double calculate_square_area(double radius) { return pow(radius, 2); }

double calculate_circle_circumference(double radius) {
  return 2 * M_PI * radius;
}

double calculate_square_perimeter(double side) { return 4 * side; }

double inches_to_cm(double inches) { return inches * 2.54; }

double cm_to_inches(double cm) { return cm / 2.54; }

double calculate_base_price(double area, double price_per_square_cm) {
  return area * price_per_square_cm;
}

double calculate_price_with_toppings(double base_price, int cheese_count,
                                     int pepperoni_count, int mushroom_count) {
  double cheese_price = 1.5;
  double pepperoni_price = 2.0;
  double mushroom_price = 1.8;

  double topping_cost = (cheese_count * cheese_price) +
                        (pepperoni_count * pepperoni_price) +
                        (mushroom_count * mushroom_price);

  return base_price + topping_cost;
}

double calculate_total_calories(double area, double calories_per_square_cm) {
  return area * calories_per_square_cm;
}

double calculate_price_per_square_cm(double price, double area) {
  if (area == 0) {
    return 0;
  }
  return price / area;
}

void print_pizza_info(PizzaInfo info) {
  printf("\n========== Pizza Information ==========\n");
  printf("Area: %.2f square centimeters\n", info.area);
  printf("Price: $%.2f\n", info.price);
  printf("Calories: %.2f kcal\n", info.calories);
  printf("Price per square cm: $%.4f\n", info.price_per_square_cm);
  printf("======================================\n\n");
}

PizzaInfo create_pizza_info(double radius, const char *type) {
  PizzaInfo info;

  if (strcmp(type, "circle") == 0) {
    info.area = calculate_circle_area(radius);
  } else if (strcmp(type, "square") == 0) {
    info.area = calculate_square_area(radius);
  } else {
    info.area = 0;
  }

  info.price = calculate_base_price(info.area, PRICE_PER_SQUARE_CM);
  info.calories = calculate_total_calories(info.area, CALORIES_PER_SQUARE_CM);
  info.price_per_square_cm =
      calculate_price_per_square_cm(info.price, info.area);

  return info;
}

double calculate_discount(double price, double discount_percentage) {
  return price * (1 - discount_percentage / 100.0);
}

int recommend_pizza_size(int people_count) {
  const int calories_per_person = 500;

  double total_calories_needed = people_count * calories_per_person;
  double radius_squared =
      total_calories_needed / (M_PI * CALORIES_PER_SQUARE_CM);
  double recommended_radius = sqrt(radius_squared);

  return (int)ceil(recommended_radius);
}

double compare_value_for_money(double area1, double price1, double area2,
                               double price2) {
  double value1 = calculate_price_per_square_cm(price1, area1);
  double value2 = calculate_price_per_square_cm(price2, area2);

  if (value1 < value2) {
    return -1;
  } else if (value1 > value2) {
    return 1;
  } else {
    return 0;
  }
}