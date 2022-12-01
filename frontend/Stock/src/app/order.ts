export interface Order {
    detail_id: string;
    worker: string;
    change: number;
    time_change: string;
}

export interface Orders {
    logs: Order[]
}