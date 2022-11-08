export interface Worker {
    id: number;
    name: string;
    surname: string;
    privilege: number;
    birthdate: string;
}

export interface WorkerSignup {
    name: string;
    surname: string;
    birthdate: string;
    username: string;
    password: string;
}