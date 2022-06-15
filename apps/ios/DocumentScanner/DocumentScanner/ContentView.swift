//
//  ContentView.swift
//  DocumentScanner
//
//  Created by Vahagn Sirunyan on 24.05.2022.
//

import SwiftUI

struct ContentView: View {
    
    @State private var showCamera: Bool = false
    @State private var image: Image?
    @State private var cpImage: Image?
    
    var body: some View {
        VStack {
            
            VStack {
                cpImage?.resizable().scaledToFit()
                image?.resizable().scaledToFit()
            }
            
            Button("Scan Document") {
                self.showCamera = true
            }.padding()
                .background(Color.green)
                .foregroundColor(Color.white)
                .cornerRadius(10)
        }.sheet(isPresented: self.$showCamera) {
            CameraView(isShown: self.$showCamera, documentImage: self.$image, cornerPointsImage: self.$cpImage)
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
