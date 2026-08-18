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
  const title = "RISC-V × OTBN — PQC 가속 세미나";
  const description = "버스와 하드웨어 구조부터 FrodoKEM·HQC·Classic McEliece 병목, OTBN 커스텀 명령어 로드맵까지 설명하는 인터랙티브 발표 자료";

  return {
    title,
    description,
    openGraph: {
      title,
      description,
      url: origin,
      type: "website",
      locale: "ko_KR",
      images: [{ url: `${origin}/og.png`, width: 1731, height: 909, alt: "RISC-V와 OTBN을 이용한 PQC 가속 세미나" }],
    },
    twitter: { card: "summary_large_image", title, description, images: [`${origin}/og.png`] },
  };
}

export default function RootLayout({ children }: Readonly<{ children: React.ReactNode }>) {
  return <html lang="ko"><body className={`${geistSans.variable} ${geistMono.variable}`}>{children}</body></html>;
}
