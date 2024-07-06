import matplotlib.pyplot as plt


if __name__ == "__main__":
    buy_limits = {}
    sell_limits = {}
    csv_path = "final_order_book.csv"

    with open(csv_path) as f:
        f.readline()
        while line := f.readline():
            line_split = line.split(",")
            if line_split[1] == "BUY":
                buy_limits[int(line_split[0])] = int(line_split[2])
            else:
                sell_limits[int(line_split[0])] = int(line_split[2])

    plt.bar(list(buy_limits.keys()), list(buy_limits.values()), color="C2")
    plt.bar(list(sell_limits.keys()), list(sell_limits.values()), color="C3")
    plt.xlabel("Price Limit")
    plt.ylabel("Volume")
    plt.title("Order Book Price Limits")
    plt.tight_layout()
    plt.savefig("final_order_book", dpi=200)
