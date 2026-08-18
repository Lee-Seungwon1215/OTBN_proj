import type { Metadata } from "next";
import { Geist, Geist_Mono } from "next/font/google";
import "./globals.css";

const geistSans = Geist({
  variable: "--font-geist-sans",
  subsets: ["latin"],
});

const geistMono = Geist_Mono({
  variable: "--font-geist-mono",
  subsets: ["latin"],
});

export const metadata: Metadata = {
  title: "그림으로 이해하는 RISC-V · OTBN · KMAC 데이터 흐름",
  description: "KMAC↔OTBN과 Host↔OTBN DMEM 전송 병목을 FrodoKEM, HQC, Classic McEliece 예제로 배우는 인터랙티브 교재",
};

export default function RootLayout({ children }: Readonly<{ children: React.ReactNode }>) {
  return (
    <html lang="ko">
      <body className={`${geistSans.variable} ${geistMono.variable}`}>{children}</body>
    </html>
  );
}
