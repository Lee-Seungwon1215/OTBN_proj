import type { Metadata } from "next";
import { Geist, Geist_Mono } from "next/font/google";
import "./globals.css";

const sans = Geist({ variable: "--font-sans", subsets: ["latin"] });
const mono = Geist_Mono({ variable: "--font-mono", subsets: ["latin"] });

export const metadata: Metadata = {
  title: "PQC Co-Design Atlas — RISC-V · OTBN · KMAC",
  description: "FrodoKEM, HQC, Classic McEliece의 병목에서 RISC-V·OTBN 커스텀 가속 설계까지 연결하는 그림 중심 교재",
};

export default function RootLayout({ children }: Readonly<{ children: React.ReactNode }>) {
  return <html lang="ko"><body className={`${sans.variable} ${mono.variable}`}>{children}</body></html>;
}
