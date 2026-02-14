"""
Floating Point Rounding Error Experiment

Tests the error accumulation of four rounding methods:
- Towards Zero: Round towards zero
- Round Up: Round towards positive infinity
- Round Down: Round towards negative infinity
- Nearest Even: Round to nearest even (IEEE 754 default)
"""

import random
import matplotlib.pyplot as plt
from typing import List, Dict


class RoundingExperiment:
    """Floating point rounding error experiment class"""

    def __init__(self, n_samples: int = 1000, value_range: tuple = (0, 10)):
        """
        Initialize experiment parameters.

        Args:
            n_samples: Number of random numbers
            value_range: Range of random numbers (min, max)
        """
        self.n_samples = n_samples
        self.value_range = value_range
        self.random_numbers = []

    def generate_random_numbers(self) -> List[float]:
        """
        Generate random decimal numbers within specified range.

        Returns:
            List of random numbers
        """
        self.random_numbers = [
            random.uniform(self.value_range[0], self.value_range[1])
            for _ in range(self.n_samples)
        ]
        return self.random_numbers

    def round_towards_zero(self, x: float) -> int:
        """
        Round towards zero (truncation).

        Args:
            x: Input value

        Returns:
            Rounded integer
        """
        return int(x)

    def round_up(self, x: float) -> int:
        """
        Round towards positive infinity (ceiling).

        Args:
            x: Input value

        Returns:
            Rounded integer
        """
        import math
        return math.ceil(x)

    def round_down(self, x: float) -> int:
        """
        Round towards negative infinity (floor).

        Args:
            x: Input value

        Returns:
            Rounded integer
        """
        import math
        return math.floor(x)

    def round_nearest_even(self, x: float) -> int:
        """
        Round to nearest even (IEEE 754 default mode).
        Round half to even.

        Args:
            x: Input value

        Returns:
            Rounded integer
        """
        import math
        fractional = x - math.floor(x)

        if fractional < 0.5:
            return math.floor(x)
        elif fractional > 0.5:
            return math.ceil(x)
        else:
            # Exactly at midpoint, choose even number
            lower = math.floor(x)
            upper = math.ceil(x)
            return lower if lower % 2 == 0 else upper

    def compute_rounding_error(self) -> Dict[str, Dict]:
        """
        Compute cumulative error for each rounding method.

        Returns:
            Dictionary containing results and errors for each rounding method
        """
        if not self.random_numbers:
            self.generate_random_numbers()

        # Compute exact value (without rounding)
        exact_sum = sum(self.random_numbers)

        # Define three rounding methods
        rounding_methods = {
            'Round Up': self.round_up,
            'Round Down': self.round_down,
            'Nearest Even': self.round_nearest_even
        }

        results = {}

        for name, method in rounding_methods.items():
            # Round each random number
            rounded_values = [method(x) for x in self.random_numbers]

            # Compute sum after rounding
            rounded_sum = sum(rounded_values)

            # Compute cumulative error
            error = rounded_sum - exact_sum
            error_percentage = (error / exact_sum) * 100 if exact_sum != 0 else 0

            results[name] = {
                'exact_sum': exact_sum,
                'rounded_sum': rounded_sum,
                'absolute_error': error,
                'error_percentage': error_percentage,
                'rounded_values': rounded_values[:10]  # Keep first 10 for display
            }

        return results

    def compute_cumulative_errors(self) -> Dict[str, List[float]]:
        """
        Compute cumulative relative errors at each step to show error progression.

        Returns:
            Dictionary with cumulative relative error arrays for each rounding method
        """
        if not self.random_numbers:
            self.generate_random_numbers()

        # Define three rounding methods
        rounding_methods = {
            'Round Up': self.round_up,
            'Round Down': self.round_down,
            'Nearest Even': self.round_nearest_even
        }

        cumulative_errors = {name: [] for name in rounding_methods.keys()}

        # Initialize running sums
        exact_running_sum = 0.0
        rounded_running_sums = {name: 0 for name in rounding_methods.keys()}

        # Compute cumulative errors at each step
        for x in self.random_numbers:
            exact_running_sum += x

            for name, method in rounding_methods.items():
                rounded_running_sums[name] += method(x)
                # Compute relative error as percentage
                if exact_running_sum != 0:
                    error = ((rounded_running_sums[name] - exact_running_sum) / exact_running_sum) * 100
                else:
                    error = 0
                cumulative_errors[name].append(error)

        return cumulative_errors

    def visualize_results(self, results: Dict[str, Dict]):
        """
        Visualize rounding error comparison results.

        Args:
            results: Result dictionary from compute_rounding_error()
        """
        methods = list(results.keys())
        absolute_errors = [results[m]['absolute_error'] for m in methods]
        error_percentages = [results[m]['error_percentage'] for m in methods]

        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))

        # Absolute error comparison
        colors = ['#4ECDC4', '#45B7D1', '#FFA07A']
        bars1 = ax1.bar(methods, absolute_errors, color=colors, alpha=0.7, edgecolor='black')
        ax1.set_ylabel('Absolute Error', fontsize=12)
        ax1.set_title('Cumulative Absolute Error by Rounding Method',
                     fontsize=14, fontweight='bold')
        ax1.grid(axis='y', alpha=0.3)
        ax1.axhline(y=0, color='black', linestyle='-', linewidth=0.5)

        # Annotate values on bars
        for bar, value in zip(bars1, absolute_errors):
            height = bar.get_height()
            ax1.text(bar.get_x() + bar.get_width()/2., height,
                    f'{value:.2f}',
                    ha='center', va='bottom' if height >= 0 else 'top',
                    fontsize=10, fontweight='bold')

        # Relative error percentage comparison
        colors = ['#4ECDC4', '#45B7D1', '#FFA07A']
        bars2 = ax2.bar(methods, error_percentages, color=colors, alpha=0.7, edgecolor='black')
        ax2.set_ylabel('Relative Error (%)', fontsize=12)
        ax2.set_title('Cumulative Relative Error by Rounding Method',
                     fontsize=14, fontweight='bold')
        ax2.grid(axis='y', alpha=0.3)
        ax2.axhline(y=0, color='black', linestyle='-', linewidth=0.5)

        # Annotate values on bars
        for bar, value in zip(bars2, error_percentages):
            height = bar.get_height()
            ax2.text(bar.get_x() + bar.get_width()/2., height,
                    f'{value:.3f}%',
                    ha='center', va='bottom' if height >= 0 else 'top',
                    fontsize=10, fontweight='bold')

        plt.tight_layout()
        plt.savefig('/Users/xiyuanyang/Desktop/Dev/CSAPP/docs/assets/Lecture4/rounding_error_comparison.svg',
                    dpi=300, bbox_inches='tight')
        print("\nChart saved to: docs/assets/Lecture4/rounding_error_comparison.svg")

    def visualize_cumulative_errors(self):
        """
        Visualize cumulative error progression as sample size increases.
        Shows 4 curves in one figure, each representing a rounding method.
        """
        cumulative_errors = self.compute_cumulative_errors()

        fig, ax = plt.subplots(1, 1, figsize=(12, 7))

        colors = {
            'Round Up': '#4ECDC4',
            'Round Down': '#45B7D1',
            'Nearest Even': '#FFA07A'
        }

        x_values = range(1, len(self.random_numbers) + 1)

        for method, errors in cumulative_errors.items():
            ax.plot(x_values, errors, label=method, color=colors[method],
                   linewidth=2, alpha=0.8)

        ax.set_xlabel('Number of Samples', fontsize=12, fontweight='bold')
        ax.set_ylabel('Cumulative Relative Error (%)', fontsize=12, fontweight='bold')
        ax.set_title('Cumulative Relative Rounding Error Progression',
                    fontsize=14, fontweight='bold')
        ax.legend(loc='best', fontsize=11, framealpha=0.9)
        ax.grid(True, alpha=0.3)
        ax.axhline(y=0, color='black', linestyle='--', linewidth=0.8, alpha=0.5)

        plt.tight_layout()
        plt.savefig('/Users/xiyuanyang/Desktop/Dev/CSAPP/docs/assets/Lecture4/rounding_error_progression.svg',
                    dpi=300, bbox_inches='tight')
        print("\nChart saved to: docs/assets/Lecture4/rounding_error_progression.svg")
        plt.show()

    def print_results(self, results: Dict[str, Dict]):
        """
        Print experiment result report.

        Args:
            results: Result dictionary from compute_rounding_error()
        """
        print("\n" + "="*80)
        print("Floating Point Rounding Error Experiment Report".center(80))
        print("="*80)
        print(f"\nExperiment Parameters:")
        print(f"  - Number of samples: {self.n_samples}")
        print(f"  - Value range: {self.value_range[0]} ~ {self.value_range[1]}")
        # Get exact sum from first method
        first_method = list(results.keys())[0]
        print(f"  - Exact sum: {results[first_method]['exact_sum']:.4f}")

        print("\n" + "-"*80)
        print(f"{'Rounding Method':<20} {'Rounded Sum':<15} {'Abs Error':<15} {'Rel Error'}")
        print("-"*80)

        for method, data in results.items():
            print(f"{method:<20} {data['rounded_sum']:<15.2f} "
                  f"{data['absolute_error']:<15.2f} {data['error_percentage']:.4f}%")

        print("-"*80)

        # Analyze results
        print("\nKey Findings:")
        min_error_method = min(results.items(),
                              key=lambda x: abs(x[1]['absolute_error']))
        print(f"  [+] Minimum error: {min_error_method[0]} "
              f"(error: {min_error_method[1]['absolute_error']:.2f})")

        max_error_method = max(results.items(),
                              key=lambda x: abs(x[1]['absolute_error']))
        print(f"  [-] Maximum error: {max_error_method[0]} "
              f"(error: {max_error_method[1]['absolute_error']:.2f})")

        print("\nSample Data (First 10 random numbers with rounding results):")
        print(f"Original values: {[f'{x:.2f}' for x in self.random_numbers[:10]]}")
        for method, data in results.items():
            print(f"{method}: {data['rounded_values']}")

        print("="*80 + "\n")


def main():
    """Main program entry point"""
    print("Starting Floating Point Rounding Error Experiment...\n")

    # Create experiment instance
    experiment = RoundingExperiment(n_samples=1000, value_range=(0, 5))

    # Generate random numbers
    print("Generating 1000 random numbers...")
    experiment.generate_random_numbers()
    print(f"Complete! Range: {min(experiment.random_numbers):.2f} ~ "
          f"{max(experiment.random_numbers):.2f}")

    # Compute rounding errors
    print("\nComputing rounding errors...")
    results = experiment.compute_rounding_error()

    # Print results
    experiment.print_results(results)

    # Visualize comparison
    print("\nGenerating comparison visualization...")
    experiment.visualize_results(results)

    # Visualize cumulative error progression
    print("\nGenerating cumulative error progression visualization...")
    experiment.visualize_cumulative_errors()

    print("\nExperiment completed!")


if __name__ == "__main__":
    main()
