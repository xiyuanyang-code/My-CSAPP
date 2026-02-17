#include "math_tool.h"
#include <stdio.h>
#include <string.h>

int main() {
  printf("========== Welcome to Pizza Shop ==========\n\n");

  double radius;
  printf("Input the radius of the pizza (cm): ");
  scanf("%lf", &radius);

  printf("\nInput the type of the pizza (square or circle): ");
  char type[10];
  scanf("%s", type);

  if (strcmp(type, "circle") != 0 && strcmp(type, "square") != 0) {
    printf("Error, the pizza type %s is not supported\n", type);
    return 1;
  }

  PizzaInfo pizza = create_pizza_info(radius, type);
  print_pizza_info(pizza);

  printf("Would you like to add toppings? (1 for yes, 0 for no): ");
  int add_toppings;
  scanf("%d", &add_toppings);

  if (add_toppings == 1) {
    int cheese_count = 0, pepperoni_count = 0, mushroom_count = 0;

    printf("Enter number of extra cheese portions: ");
    scanf("%d", &cheese_count);

    printf("Enter number of pepperoni portions: ");
    scanf("%d", &pepperoni_count);

    printf("Enter number of mushroom portions: ");
    scanf("%d", &mushroom_count);

    pizza.price = calculate_price_with_toppings(
        pizza.price, cheese_count, pepperoni_count, mushroom_count);
    printf("\nPrice updated with toppings!\n");
    print_pizza_info(pizza);
  }

  printf("Do you have a membership discount? (1 for yes, 0 for no): ");
  int has_discount;
  scanf("%d", &has_discount);

  if (has_discount == 1) {
    double discount_percentage;
    printf("Enter discount percentage (e.g., 10 for 10%%): ");
    scanf("%lf", &discount_percentage);

    double original_price = pizza.price;
    pizza.price = calculate_discount(pizza.price, discount_percentage);
    printf("\nDiscount applied: %.2f%% -> $%.2f\n", discount_percentage,
           original_price - pizza.price);
    print_pizza_info(pizza);
  }

  if (strcmp(type, "circle") == 0) {
    double circumference = calculate_circle_circumference(radius);
    printf("Circumference: %.2f cm\n", circumference);
  } else {
    double perimeter = calculate_square_perimeter(radius);
    printf("Perimeter: %.2f cm\n", perimeter);
  }

  double radius_inches = cm_to_inches(radius);
  printf("\nSize in inches: %.2f inches\n", radius_inches);

  printf("\nHow many people will be eating? ");
  int people_count;
  scanf("%d", &people_count);

  int recommended_radius = recommend_pizza_size(people_count);
  printf("Recommended pizza radius for %d people: %d cm\n", people_count,
         recommended_radius);

  if (radius < recommended_radius) {
    printf("Note: Your pizza might be too small for %d people!\n",
           people_count);
  } else {
    printf("Your pizza size is good for %d people!\n", people_count);
  }

  printf("\n========================================\n");
  printf("Thank you for your order!\n");
  printf("Total price: $%.2f\n", pizza.price);
  printf("========================================\n");

  return 0;
}