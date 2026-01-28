#!/usr/bin/env python3

def order_data_migration(inputFile, outputFile): 
    with open(inputFile, "r") as infile, open(outputFile, "w") as outfile:
        for line_number, line in enumerate(infile, start=1):
            line = line.strip()
            if not line:
                continue

            parts = line.split(",")

            try:
                #Old file
                orderID         = parts[0]
                customerID      = parts[1]
                cost            = parts[2]
                rack            = parts[3]
                pickUp          = parts[4]
                paid            = parts[5]
                pieceTotal      = parts[6]
                discountApplied = parts[7]
                discount        = parts[8]
                discountedCost  = parts[9]
                deposit         = parts[10]

                #Everything after deposit stays the same
                remainder = ",".join(parts[11:])

                #New entries
                taxable = "0"
                tax = "0"
                finalCost = discountedCost

                new_line = ",".join([
                    orderID,
                    customerID,
                    cost,
                    rack,
                    pickUp,
                    paid,
                    pieceTotal,
                    discountApplied,
                    discount,
                    taxable,
                    tax,
                    finalCost,
                    deposit,
                    remainder
                ])

                outfile.write(new_line + "\n")

            except IndexError:
                print(f"[ERROR] Line {line_number} is malformed and was skipped:")
                print(line)




def main():
    import sys
    if len(sys.arg) != 3: 
        return
    
    inputFile = sys.argv[1]
    outputFile = sys.argv[2]

    order_data_migration(inputFile, outputFile)

if __name__ == "__main__":
    main()

