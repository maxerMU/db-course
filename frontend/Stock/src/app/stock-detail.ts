export interface StockDetail {
    part_number: string,
    part_name: string,
    producer_name: string,
    producer_country: string
    amount: number,
}

export interface DetailInStock {
  part_number: string;
  quantity: number;
}

export interface StockDetails {
  details: StockDetail[]
}