import type { Metadata } from "next";
import { headers } from "next/headers";
import { Geist, Geist_Mono } from "next/font/google";
import "./globals.css";

const geistSans = Geist({ variable: "--font-geist-sans", subsets: ["latin"] });
const geistMono = Geist_Mono({ variable: "--font-geist-mono", subsets: ["latin"] });

export async function generateMetadata(): Promise<Metadata> {
  const requestHeaders = await headers();
  const host = requestHeaders.get("x-forwarded-host") ?? requestHeaders.get("host") ?? "localhost:3000";
  const protocol = requestHeaders.get("x-forwarded-proto") ?? (host.startsWith("localhost") ? "http" : "https");
  const origin = `${protocol}://${host}`;
  const title = "PQC Bottleneck Atlas — FrodoKEM·HQC·McEliece × OTBN";
  const description = "세 PQC 알고리즘의 코드상·실측상 병목을 비교하고 RISC-V·OTBN 적용 방향을 고르는 인터랙티브 교재";

  return {
    title,
    description,
    openGraph: {
      title,
      description,
      url: origin,
      type: "website",
      locale: "ko_KR",
      images: [{ url: `${origin}/og.png`, width: 1731, height: 909, alt: "PQC Bottleneck Atlas" }],
    },
    twitter: {
      card: "summary_large_image",
      title,
      description,
      images: [`${origin}/og.png`],
    },
  };
}

export default function RootLayout({ children }: Readonly<{ children: React.ReactNode }>) {
  return (
    <html lang="ko">
      <body className={`${geistSans.variable} ${geistMono.variable}`}>{children}</body>
    </html>
  );
}
