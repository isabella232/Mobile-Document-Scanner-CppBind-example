package com.example.docscanapp

import android.app.Application


class DocScannerApplication : Application() {

    override fun onCreate() {
        super.onCreate()
        System.loadLibrary("document_scanner")
    }
}
