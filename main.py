import io
import json
import requests
import tkinter as tk
from tkinter import ttk, messagebox, simpledialog
from PIL import Image, ImageTk

# ==========================================
# Constantes
# ==========================================
JSON_FILE = "anime_data.json"
MAL_API_URL = "https://api.myanimelist.net/v2/anime"
CLIENT_ID = "0d269be41a81866d847864c6535c7291" # Substitua pelo seu CLIENT_ID da API MAL

# ==========================================
# Funções Utilitárias
# ==========================================
def load_anime_data():
    """Carrega os dados salvos localmente no arquivo JSON."""
    try:
        with open(JSON_FILE, "r", encoding="utf-8") as file:
            return json.load(file)
    except (FileNotFoundError, json.JSONDecodeError):
        return {}

def save_anime_data(data):
    """Salva os dados no arquivo JSON."""
    with open(JSON_FILE, "w", encoding="utf-8") as file:
        json.dump(data, file, indent=4)

def search_anime(query):
    """Realiza a busca de anime na API do MyAnimeList."""
    headers = {"X-MAL-CLIENT-ID": CLIENT_ID}
    params = {"q": query, "limit": 5, "fields": "main_picture"}
    
    try:
        response = requests.get(MAL_API_URL, headers=headers, params=params)
        if response.status_code == 200:
            return response.json().get("data", [])
    except requests.exceptions.RequestException as e:
        print(f"Erro na conexão com a API: {e}")
    
    return []

# ==========================================
# Classes de Interface Gráfica (UI)
# ==========================================
class SearchResultsModal:
    def __init__(self, parent, results, anime_table, main_app):
        self.parent = parent
        self.results = results
        self.anime_table = anime_table
        self.main_app = main_app
        
        self.modal = tk.Toplevel(parent)
        self.modal.title("Selecionar Anime")
        self.modal.geometry("600x350")
        self.modal.configure(bg="#2C1E3D")
        
        # Cache para imagens do modal (para não baixar novamente)
        self.modal_image_cache = {}
        
        self.create_widgets()

    def create_widgets(self):
        # Frame que organiza a listagem e a imagem lado a lado
        self.content_frame = tk.Frame(self.modal, bg="#2C1E3D")
        self.content_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

        # Esquerda: listbox com os títulos
        self.list_frame = tk.Frame(self.content_frame, bg="#2C1E3D")
        self.list_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        
        self.lbl_lista = tk.Label(self.list_frame, text="Selecione um anime:", font=("Arial", 14), bg="#2C1E3D", fg="#FFFFFF")
        self.lbl_lista.pack(pady=5)
        
        self.listbox = tk.Listbox(self.list_frame, font=("Arial", 12), bg="#6247AA", fg="#FFFFFF", selectmode=tk.SINGLE)
        self.listbox.pack(pady=5, fill=tk.BOTH, expand=True)

        # Direita: área para exibir a capa
        self.image_frame = tk.Frame(self.content_frame, bg="#2C1E3D")
        self.image_frame.pack(side=tk.LEFT, fill=tk.BOTH, padx=10)
        
        self.cover_label = tk.Label(self.image_frame, bg="#2C1E3D")
        self.cover_label.pack(pady=5)

        # Frame de botões (Adicionado)
        self.btn_frame = tk.Frame(self.modal, bg="#2C1E3D")
        self.btn_frame.pack(fill=tk.X, pady=10)
        
        self.btn_confirmar = tk.Button(self.btn_frame, text="Confirmar Seleção", command=self.confirm_selection)
        self.btn_confirmar.pack()

        # Preenche a listbox com os títulos dos animes
        for anime in self.results:
            title = anime["node"]["title"]
            self.listbox.insert(tk.END, title)

        # Evento completado: dispara quando o usuário clica em um item
        self.listbox.bind("<<ListboxSelect>>", self.on_select)

    def on_select(self, event):
        """Carrega e exibe a imagem de capa do anime selecionado."""
        selecao = self.listbox.curselection()
        if not selecao:
            return
            
        index = selecao[0]
        anime_selecionado = self.results[index]
        image_url = anime_selecionado["node"]["main_picture"]["medium"]

        # Verifica se a imagem já está no cache
        if image_url in self.modal_image_cache:
            photo = self.modal_image_cache[image_url]
            self.cover_label.config(image=photo)
            self.cover_label.image = photo
        else:
            # Baixa a imagem da internet
            try:
                response = requests.get(image_url)
                img_data = Image.open(io.BytesIO(response.content))
                img_data = img_data.resize((150, 220), Image.Resampling.LANCZOS)
                
                photo = ImageTk.PhotoImage(img_data)
                self.modal_image_cache[image_url] = photo
                
                self.cover_label.config(image=photo)
                self.cover_label.image = photo
            except Exception as e:
                print(f"Erro ao carregar imagem: {e}")

    def confirm_selection(self):
        """Ação do botão confirmar."""
        selecao = self.listbox.curselection()
        if not selecao:
            messagebox.showwarning("Aviso", "Por favor, selecione um anime na lista.")
            return
            
        index = selecao[0]
        anime_selecionado = self.results[index]
        
        # Aqui você adiciona a lógica para salvar na sua tabela
        # self.main_app.add_to_table(anime_selecionado)
        print(f"Selecionado: {anime_selecionado['node']['title']}")
        
        self.modal.destroy()# alteracao arquivo
