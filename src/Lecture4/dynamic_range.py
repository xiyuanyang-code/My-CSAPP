"""Dynamic range analysis for simplified floating-point representation.

Floating-point format with 4 exponent bits + 3 fraction bits, positive numbers only (sign bit = 0).
"""

from fractions import Fraction
from typing import List, Tuple
import matplotlib.pyplot as plt
import numpy as np


class FloatDecoder:
    """Simplified floating-point decoder.

    Attributes:
        k: Number of exponent bits
        n: Number of fraction bits
        bias: Bias value
    """

    def __init__(self, k: int = 4, n: int = 3):
        """Initialize decoder.

        Args:
            k: Number of exponent bits
            n: Number of fraction bits
        """
        self.k = k
        self.n = n
        self.bias = (1 << (k - 1)) - 1  # 2^(k-1) - 1

    def decode(self, exp_bits: int, frac_bits: int) -> Tuple[int, int, Fraction, str]:
        """Decode floating-point number.

        Args:
            exp_bits: Integer value of exponent bits
            frac_bits: Integer value of fraction bits

        Returns:
            (exp, frac, value, category):
                - exp: Integer value of exponent bits
                - frac: Integer value of fraction bits
                - value: Exact fractional value
                - category: Type ('denorm', 'norm', 'inf')
        """
        exp = exp_bits
        frac = frac_bits

        # Determine category
        if exp == (1 << self.k) - 1:  # All exponent bits are 1
            if frac == 0:
                return exp, frac, None, "inf"
            else:
                return exp, frac, None, "nan"
        elif exp == 0:  # Denormalized number
            # E = 1 - Bias, M = frac / 2^n
            e = 1 - self.bias
            m = Fraction(frac, 1 << self.n)
            if e >= 0:
                value = m * Fraction(2**e, 1)
            else:
                value = m / Fraction(2 ** (-e), 1)
            return exp, frac, value, "denorm"
        else:  # Normalized number
            # E = exp - Bias, M = 1 + frac / 2^n
            e = exp - self.bias
            m = Fraction(1 << self.n, 1 << self.n) + Fraction(frac, 1 << self.n)
            if e >= 0:
                value = m * Fraction(2**e, 1)
            else:
                value = m / Fraction(2 ** (-e), 1)
            return exp, frac, value, "norm"

    def generate_table(self) -> List[Tuple[int, int, int, Fraction, str]]:
        """Generate table of all possible floating-point representations.

        Returns:
            List containing all floating-point info, each item is (s, exp, frac, E, value, category)
        """
        results = []
        s = 0  # Only positive numbers

        for exp in range(1 << self.k):
            for frac in range(1 << self.n):
                exp_val, frac_val, value, category = self.decode(exp, frac)

                if category in ["denorm", "norm"]:
                    # Calculate E value
                    if category == "denorm":
                        E = 1 - self.bias
                    else:
                        E = exp - self.bias

                    results.append((s, exp, frac, E, value, category))
                elif category == "inf":
                    results.append((s, exp, frac, None, None, "inf"))
                # Skip NaN

        return results

    def format_table(self, data: List[Tuple]) -> str:
        """Format and output table.

        Args:
            data: List of floating-point data

        Returns:
            Formatted table string
        """
        lines = []
        lines.append(
            "Floating-Point Representation Table (4 exponent bits + 3 fraction bits)"
        )
        lines.append("=" * 90)
        lines.append(
            f"{'s':<2} {'exp':<6} {'frac':<6} {'E':<4} {'Fraction':<25} {'Category':<12}"
        )
        lines.append("-" * 90)

        for s, exp, frac, E, value, category in data:
            if value is not None:
                # Always display as fraction (e.g., "1/2", "3/4", "9/8")
                if value.denominator == 1:
                    value_str = f"{value.numerator}"
                else:
                    value_str = f"{value.numerator}/{value.denominator}"
            else:
                value_str = "Infinity"

            E_str = str(E) if E is not None else "N/A"
            category_str = {
                "denorm": "Denormalized",
                "norm": "Normalized",
                "inf": "Infinity",
            }.get(category, category)

            # Format binary with proper padding
            exp_bin = format(exp, f"0{self.k}b")
            frac_bin = format(frac, f"0{self.n}b")

            lines.append(
                f"{s:<2} {exp_bin:<6} {frac_bin:<6} {E_str:<4} {value_str:<25} {category_str:<12}"
            )

        return "\n".join(lines)


def plot_distribution(
    data: List[Tuple], output_path: str = None, use_log_scale: bool = True
):
    """Plot distribution of floating-point numbers on number line.

    Args:
        data: List of floating-point data
        output_path: Optional image save path
        use_log_scale: Whether to use logarithmic scale for x-axis
    """
    # Classify data by exponent value
    denorm_values = []  # exp = 0000
    norm_by_exp = {}  # Group normalized numbers by exponent

    for s, exp, frac, E, value, category in data:
        if value is not None:
            if category == "denorm":
                denorm_values.append(float(value))
            elif category == "norm":
                if exp not in norm_by_exp:
                    norm_by_exp[exp] = []
                norm_by_exp[exp].append(float(value))

    # Create figure
    fig, ax = plt.subplots(figsize=(18, 10))

    # Color palette for different exponent values
    colors = plt.cm.RdYlGn_r(np.linspace(0.2, 0.8, len(norm_by_exp)))

    # Plot denormalized numbers at the bottom
    if denorm_values:
        ax.scatter(
            denorm_values,
            [0] * len(denorm_values),
            c="#1f77b4",
            s=30,
            alpha=0.7,
            marker="o",
            label=f"Denormalized (E=-6)",
            zorder=3,
            edgecolors="darkblue",
            linewidth=0.5,
        )

    y_pos = 1
    legend_elements = []

    # Plot normalized numbers grouped by exponent
    for exp, values in sorted(norm_by_exp.items()):
        E = exp - 7  # Calculate E value
        color = colors[y_pos - 1]

        # Add stem lines
        for val in values:
            ax.plot(
                [val, val], [0, y_pos], color=color, alpha=0.3, linewidth=0.5, zorder=1
            )

        # Plot points
        ax.scatter(
            values,
            [y_pos] * len(values),
            c=[color],
            s=25,
            alpha=0.8,
            marker="o",
            zorder=2,
            edgecolors="black",
            linewidth=0.3,
        )

        legend_elements.append(
            plt.Line2D(
                [0],
                [0],
                marker="o",
                color="w",
                markerfacecolor=color,
                markersize=6,
                label=f"E={E}",
            )
        )
        y_pos += 1

    # Add infinity marker at the top (using circle like other points)
    max_value = max(norm_by_exp[max(norm_by_exp.keys())]) if norm_by_exp else 0
    ax.scatter(
        [max_value * 1.05],
        [y_pos],
        c="red",
        s=80,
        marker="o",
        label=r"$\infty$",
        zorder=4,
        edgecolors="darkred",
        linewidth=1.5,
    )
    ax.text(
        max_value * 1.05,
        y_pos + 0.2,
        r"$\infty$",
        fontsize=12,
        color="red",
        ha="center",
        va="bottom",
        fontweight="bold",
    )

    # Set axis properties
    ax.set_xlabel("Value", fontsize=13, fontweight="bold")
    ax.set_ylabel("Exponent (E)", fontsize=13, fontweight="bold")
    scale_type = "Logarithmic" if use_log_scale else "Linear"
    ax.set_title(
        f"Distribution of Floating-Point Numbers (4-bit exp + 3-bit frac) - {scale_type} Scale",
        fontsize=15,
        fontweight="bold",
        pad=20,
    )

    # Set x-scale based on parameter
    if use_log_scale:
        ax.set_xscale("log", base=2)
        ax.set_xlim(0.001, max_value * 1.15)
    else:
        ax.set_xscale("linear")
        ax.set_xlim(-5, max_value * 1.15)

    # Set y-axis
    ax.set_yticks(range(y_pos + 1))
    ax.set_yticklabels(
        ["Denorm"] + [f"E={e-7}" for e in sorted(norm_by_exp.keys())] + [r"$\infty$"],
        fontsize=9,
    )
    ax.set_ylim(-0.5, y_pos + 0.5)

    # Add grid
    ax.grid(True, alpha=0.2, axis="x", linestyle="--")
    ax.axhline(y=0, color="black", linewidth=1, alpha=0.3)

    # Create legend
    legend_elements.insert(
        0,
        plt.Line2D(
            [0],
            [0],
            marker="o",
            color="w",
            markerfacecolor="#1f77b4",
            markersize=8,
            label="Denormalized",
        ),
    )
    legend_elements.append(
        plt.Line2D(
            [0],
            [0],
            marker="*",
            color="w",
            markerfacecolor="red",
            markersize=12,
            label="Infinity",
        )
    )

    ax.legend(
        handles=legend_elements, loc="upper left", fontsize=9, ncol=2, framealpha=0.9
    )

    # Adjust layout
    plt.tight_layout()

    if output_path:
        plt.savefig(output_path)
        print(f"Chart saved to: {output_path}")


def plot_gap_growth(data: List[Tuple], output_path: str = None):
    """Plot the gap between adjacent floating-point numbers.

    Shows how the numerical difference between adjacent representable values grows
    as the values increase.

    Args:
        data: List of floating-point data
        output_path: Optional image save path
    """
    # Filter valid values and sort
    valid_values = []
    categories = []  # Track category for color coding

    for s, exp, frac, E, value, category in data:
        if value is not None:
            valid_values.append((float(value), exp, frac))
            categories.append(category)

    # Sort by value
    valid_values.sort(key=lambda x: x[0])

    # Calculate gaps between adjacent values
    values = [v[0] for v in valid_values]
    gaps = []
    exps = []
    gap_categories = []

    for i in range(len(valid_values) - 1):
        curr_val, curr_exp, curr_frac = valid_values[i]
        next_val, next_exp, next_frac = valid_values[i + 1]

        gap = next_val - curr_val
        gaps.append(gap)
        exps.append(curr_exp)
        gap_categories.append(categories[i])

    # Create figure
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(14, 10))

    # Plot 1: Gap vs Value (log-log scale) with color coding
    for i, (val, gap, cat) in enumerate(zip(values[:-1], gaps, gap_categories)):
        color = "lightblue" if cat == "denorm" else "lightgreen"
        edge_color = "blue" if cat == "denorm" else "green"
        ax1.scatter(
            val,
            gap,
            c=color,
            s=30,
            alpha=0.7,
            edgecolors=edge_color,
            linewidth=0.5,
            zorder=3,
        )

    # Add region backgrounds
    denorm_max = max([v for v, c in zip(values, categories) if c == "denorm"])
    ax1.axvspan(0, denorm_max, alpha=0.15, color="blue", label="Denorm Region")
    ax1.axvspan(denorm_max, max(values), alpha=0.15, color="green", label="Norm Region")

    ax1.set_xscale("log", base=2)
    ax1.set_yscale("log", base=2)
    ax1.set_xlabel("Value", fontsize=12, fontweight="bold")
    ax1.set_ylabel("Gap to Next Value", fontsize=12, fontweight="bold")
    ax1.set_title(
        "Gap Between Adjacent Floating-Point Numbers (Log-Log Scale)",
        fontsize=14,
        fontweight="bold",
    )
    ax1.grid(True, alpha=0.3, linestyle="--", which="both")
    ax1.legend(loc="upper left", fontsize=9)

    # Plot 2: Gap vs Index with color coding
    for i, (gap, cat) in enumerate(zip(gaps, gap_categories)):
        color = "lightblue" if cat == "denorm" else "lightgreen"
        edge_color = "blue" if cat == "denorm" else "green"
        ax2.scatter(
            i,
            gap,
            c=color,
            s=30,
            alpha=0.7,
            edgecolors=edge_color,
            linewidth=0.5,
            zorder=3,
        )

    # Add connecting lines
    ax2.plot(
        range(len(gaps)), gaps, "-", color="gray", alpha=0.3, linewidth=0.5, zorder=1
    )

    # Add region backgrounds
    denorm_count = sum(1 for c in gap_categories if c == "denorm")
    ax2.axvspan(0, denorm_count, alpha=0.15, color="blue")
    ax2.axvspan(denorm_count, len(gaps), alpha=0.15, color="green")

    ax2.set_xlabel("Index (sorted by value)", fontsize=12, fontweight="bold")
    ax2.set_ylabel("Gap", fontsize=12, fontweight="bold")
    ax2.set_title("Gap Growth Pattern (Linear Scale)", fontsize=14, fontweight="bold")
    ax2.grid(True, alpha=0.3, linestyle="--")
    ax2.set_yscale("log", base=2)

    # Add legend for this plot
    from matplotlib.patches import Patch

    legend_elements = [
        Patch(facecolor="lightblue", edgecolor="blue", alpha=0.7, label="Denorm Gap"),
        Patch(facecolor="lightgreen", edgecolor="green", alpha=0.7, label="Norm Gap"),
    ]
    ax2.legend(handles=legend_elements, loc="upper left", fontsize=9)

    plt.tight_layout()

    if output_path:
        plt.savefig(output_path, format="svg", bbox_inches="tight")
        print(f"Gap growth chart saved to: {output_path}")


def main():
    """Main function."""
    # Create decoder
    decoder = FloatDecoder(k=4, n=3)

    # Generate table
    table_data = decoder.generate_table()

    # Output table
    print(decoder.format_table(table_data))

    # Statistics
    denorm_count = sum(1 for _, _, _, _, _, cat in table_data if cat == "denorm")
    norm_count = sum(1 for _, _, _, _, _, cat in table_data if cat == "norm")
    inf_count = sum(1 for _, _, _, _, _, cat in table_data if cat == "inf")

    print("\n" + "=" * 90)
    print("Statistics:")
    print(f"  Denormalized numbers: {denorm_count}")
    print(f"  Normalized numbers: {norm_count}")
    print(f"  Infinity: {inf_count}")
    print(f"  Total: {len(table_data)}")
    print("=" * 90)

    # Plot distribution with logarithmic scale
    plot_distribution(
        table_data,
        output_path="docs/assets/Lecture4/dynamic_range_log.pdf",
        use_log_scale=True,
    )
    plot_distribution(
        table_data,
        output_path="docs/assets/Lecture4/dynamic_range_log.svg",
        use_log_scale=True,
    )

    # Plot distribution with linear scale
    plot_distribution(
        table_data,
        output_path="docs/assets/Lecture4/dynamic_range_linear.pdf",
        use_log_scale=False,
    )
    plot_distribution(
        table_data,
        output_path="docs/assets/Lecture4/dynamic_range_linear.svg",
        use_log_scale=False,
    )

    # Plot gap growth curve
    plot_gap_growth(table_data, output_path="docs/assets/Lecture4/gap_growth.svg")


if __name__ == "__main__":
    main()
