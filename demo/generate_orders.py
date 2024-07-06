from numpy import random as np_random
import random
import csv


def get_random_price(mean, scale, side):
    # return max(1, int((np_random.normal(mean, scale) + np_random.normal(mean, scale * .025) + np_random.normal(mean, scale * .05)) / 3))
    return max(1, int(np_random.normal(mean * (1 + .5 * (side - .5)), scale)))


def generate_order_id(used_order_ids):
    new_id = random.randint(1, 10_000_000)
    while new_id in used_order_ids:
        new_id = random.randint(1, 10_000_000)
    used_order_ids.add(new_id)
    return new_id


def generate_order(used_order_ids):
    order_id = generate_order_id(used_order_ids)
    order_side = 0 if random.choice(["BUY", "SELL"]) == "BUY" else 1
    price = get_random_price(500, 100, order_side)
    volume = max(1, int(np_random.normal(loc=100, scale=300)))
    return order_id, 0, order_side, price, volume


def generate_delete(existing_ids):
    if not existing_ids:
        return None
    idx = random.randint(0, len(existing_ids) - 1)
    order_id_to_delete = existing_ids[idx]
    existing_ids.pop(idx)
    return order_id_to_delete, 1


if __name__ == "__main__":
    used_order_ids = set()
    existing_order_ids = []
    operations = []

    num_operations = 1_000_000

    for _ in range(num_operations):
        if random.random() < 0.8 or not existing_order_ids:  # 80% of placed orders
            new_order = generate_order(used_order_ids)
            existing_order_ids.append(new_order[0])
            operations.append(("PLACE", new_order))
        else:
            delete_operation = generate_delete(existing_order_ids)
            if delete_operation:
                operations.append(("DELETE", delete_operation))

    csv_filename = r'sample_operations.csv'
    with open(csv_filename, 'w', newline='') as csvfile:
        csvwriter = csv.writer(csvfile)
        csvwriter.writerow(['Operation', 'Order ID', 'Type', 'Price', 'Volume'])
        for operation in operations:
            op_type = operation[0]
            if op_type == 'PLACE':
                order = operation[1]
                csvwriter.writerow([op_type, order[0], order[2], order[3], order[4]])
            elif op_type == 'DELETE':
                delete_info = operation[1]
                csvwriter.writerow([op_type, delete_info[0], '', '', ''])

    print(f"CSV file '{csv_filename}' has been generated with {num_operations} operations.")
